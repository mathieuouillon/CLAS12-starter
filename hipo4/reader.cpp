//******************************************************************************
//*       ██╗  ██╗██╗██████╗  ██████╗     ██╗  ██╗    ██████╗                  *
//*       ██║  ██║██║██╔══██╗██╔═══██╗    ██║  ██║   ██╔═████╗                 *
//*       ███████║██║██████╔╝██║   ██║    ███████║   ██║██╔██║                 *
//*       ██╔══██║██║██╔═══╝ ██║   ██║    ╚════██║   ████╔╝██║                 *
//*       ██║  ██║██║██║     ╚██████╔╝         ██║██╗╚██████╔╝                 *
//*       ╚═╝  ╚═╝╚═╝╚═╝      ╚═════╝          ╚═╝╚═╝ ╚═════╝                  *
//************************ Jefferson National Lab (2017) ***********************
/*
 *   Copyright (c) 2017.  Jefferson Lab (JLab). All rights reserved. Permission
 *   to use, copy, modify, and distribute  this software and its documentation
 *   for educational, research, and not-for-profit purposes, without fee and
 *   without a signed licensing agreement.
 *
 *   IN NO EVENT SHALL JLAB BE LIABLE TO ANY PARTY FOR DIRECT, INDIRECT, SPECIAL
 *   INCIDENTAL, OR CONSEQUENTIAL DAMAGES, INCLUDING LOST PROFITS, ARISING
 *   OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF JLAB HAS
 *   BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *   JLAB SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *   PURPOSE. THE HIPO DATA FORMAT SOFTWARE AND ACCOMPANYING DOCUMENTATION, IF
 *   ANY, PROVIDED HEREUNDER IS PROVIDED "AS IS". JLAB HAS NO OBLIGATION TO
 *   PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
 *
 *   This software was developed under the United States Government license.
 *   For more information contact author at gavalian@jlab.org
 *   Department of Experimental Nuclear Physics, Jefferson Lab.
 */
/*
  * File:   reader.cpp
  * Author: gavalian
  *
  * Additions by: dglazier
  * Created on April 11, 2017, 2:07 PM
  */

#include "reader.h"
#include "hipoexceptions.h"
#include "record.h"

#include <cstdlib>

/**
 * HIPO namespace is used for the classes that read/write
 * files and records.
 */
namespace hipo {
/**
  * The constructor for reader, printWarning routine
  * will printout a warning message if the library
  * was not compiled with compression libraries LZ4 or GZIP
  */
reader::reader() {
    printWarning();
}

/**
* The constructor for reader, printWarning routine
* will printout a warning message if the library
* was not compiled with compression libraries LZ4 or GZIP.
* @param fileName - input file which will be access.
* @param dict - reference to dictionary object.
* @param verbose - verbosity
*/
reader::reader(const std::string_view file, hipo::dictionary& dict, const short verbose) {
    printWarning();

    _verbose = verbose;

    open(file.data());
    readDictionary(dict);
}

/**
   * Default destructor. Does nothing
   */
reader::~reader() {
    if (inputStream.is_open() == true) {
        inputStream.close();
    }
}

void reader::about() const {
    utils::printLogo();
}

/**
   * Open file, if file stream is open, it is closed first.
   * At open time verification of file structure is performed.
   * If the signature does not match EVIO/HIPO template, the
   * file will be closed and warning message is printed.
   * @param filename - name of the file to open
   */
void reader::open(const char* filename) {

    if (inputStream.is_open() == true) {
        inputStream.close();
    }

    inputStream.open(filename, std::ios::binary);
    inputStream.seekg(0, std::ios_base::end);
    inputStreamSize = inputStream.tellg();
    inputStream.seekg(0, std::ios_base::beg);
    if (inputStream.is_open() == false) {
        printf("[ERROR] something went wrong with openning file : %s\n",
               filename);
        return;
    }
    readHeader();
    readIndex();
}

/**
 * Reads the file header. The endiannes is determined for bytes
 * swap. The header structure will be filled with file parameters.
 */
void reader::readHeader() {

    std::vector<char> headerBuffer;
    headerBuffer.resize(80);
    inputStream.read(&headerBuffer[0], 80);

    header.uniqueid = *(reinterpret_cast<int*>(&headerBuffer[0]));
    header.filenumber = *(reinterpret_cast<int*>(&headerBuffer[4]));
    header.headerLength = *(reinterpret_cast<int*>(&headerBuffer[8]));
    header.recordCount = *(reinterpret_cast<int*>(&headerBuffer[12]));

    header.indexArrayLength = *(reinterpret_cast<int*>(&headerBuffer[16]));
    int word_8 = *(reinterpret_cast<int*>(&headerBuffer[20]));

    header.userHeaderLength = *(reinterpret_cast<int*>(&headerBuffer[24]));
    header.magicNumber = *(reinterpret_cast<int*>(&headerBuffer[28]));
    header.userRegister = *(reinterpret_cast<long*>(&headerBuffer[32]));
    header.trailerPosition = *(reinterpret_cast<long*>(&headerBuffer[40]));
    // If magic word is reversed, then the file was written in BIG_ENDIAN
    // format, the bytes have to be swapped
    if (header.magicNumber == 0x0001dac0) {
        printf(" THIS FILE IS BIG ENDIAN: SWAPPING BYTES\n");
        header.uniqueid = __builtin_bswap32(header.uniqueid);
        header.filenumber = __builtin_bswap32(header.filenumber);
        header.headerLength = __builtin_bswap32(header.headerLength);
        header.recordCount = __builtin_bswap32(header.recordCount);
        header.userHeaderLength = __builtin_bswap32(header.userHeaderLength);
        header.indexArrayLength = __builtin_bswap32(header.indexArrayLength);
        word_8 = __builtin_bswap32(word_8);
        header.userRegister = __builtin_bswap64(header.userRegister);
        header.trailerPosition = __builtin_bswap64(header.trailerPosition);
    }

    header.version = word_8 & 0x000000FF;
    header.bitInfo = (word_8 >> 8) & 0x00FFFFFF;
    header.firstRecordPosition = 4 * header.headerLength + header.userHeaderLength;
    if (_verbose) {
        printf("----------------------------------------\n");
        printf("**** reader:: header version   : %d \n", header.version);
        printf("**** reader:: header length    : %d \n", header.headerLength * 4);
        printf("**** reader:: first record pos : %lu\n", header.firstRecordPosition);
        printf("**** reader:: trailer position : %lu\n", header.trailerPosition);
        printf("**** reader:: file size        : %lu\n", inputStreamSize);
        printf("----------------------------------------\n");
    }
}

/**
 * Reads run index from the file. The index is in the last record of the
 * file, and the pointer to that record is contained in the File Header.
 * If the file was not properly closed event index will not be loaded
 * then file has to be opened in sequential more, to read record by record.
 * in sequential mode the random access is not avilable.
 */
void reader::readIndex() {

    inputRecord.readRecord(inputStream, header.trailerPosition, 0);
    if (_verbose)
        printf("*** reader:: trailer record event count : %d\n", inputRecord.getEventCount());

    //a catch for broken files
    //can use hiporeader.getNRecords() to see if succesfull (=-1 if not)
    if (inputRecord.getEventCount() == 0)
        return;  //dglazier

    hipo::event dataevent;
    inputRecord.readHipoEvent(dataevent, 0);
    if (_verbose)
        dataevent.show();
    hipo::structure base;
    dataevent.getStructure(base, 32111, 1);
    if (_verbose)
        base.show();
    readerEventIndex.clear();
    int rows = base.getSize() / 32;

    //printf(" number of rows = %d\n",rows);
    for (int i = 0; i < rows; i++) {
        long position = base.getLongAt(i * 8);
        int entries = base.getIntAt(rows * 12 + i * 4);
        long uid1 = base.getLongAt(rows * 16 + i * 8);
        if (tagsToRead.empty()) {
            readerEventIndex.addSize(entries);
            readerEventIndex.addPosition(position);
        } else {
            bool accept = false;
            for (long jr : tagsToRead) {
                if (jr == uid1)
                    accept = true;
            }
            if (accept == true) {
                readerEventIndex.addSize(entries);
                readerEventIndex.addPosition(position);
            }
        }
    }
    readerEventIndex.rewind();
    //printf("**** reader:: header version   : %d \n",readerEventIndex.getMaxEvents());
    if (_verbose)
        printf("**** reader::  # of events     : %d \n", readerEventIndex.getMaxEvents());
}

/**
 * Checks if there are more events in the file to advance to.
 * @return true if there are events left to read, false - otherwise
 */
bool reader::hasNext() {
    return readerEventIndex.canAdvance();
}

/**
 * Reads next event from the file, the event pointer is automatically
 * advanced to the next event.
 * @param reference to the event object to be filled from the record.
 * @return true if the event was successfully read, and false otherwise
 */
bool reader::next(hipo::event& dataevent) {
    if (readerEventIndex.canAdvance() == false)
        return false;
    int recordNumber = readerEventIndex.getRecordNumber();
    readerEventIndex.advance();

    if (int recordToBeRead = readerEventIndex.getRecordNumber(); recordToBeRead != recordNumber) {
        long position = readerEventIndex.getPosition(recordToBeRead);
        inputRecord.readRecord(inputStream, position, 0);
    }
    
    int eventNumberInRecord = readerEventIndex.getRecordEventNumber();
    inputRecord.readHipoEvent(dataevent, eventNumberInRecord);
    return true;
}

/**
 * Reads current event from the record without advancing the current event
 * position. Multiple reads can be performed on the same event.
 * @param reference to the event object to be read
 */
void reader::read(hipo::event& dataevent) {
    int eventNumberInRecord = readerEventIndex.getRecordEventNumber();
    inputRecord.readHipoEvent(dataevent, eventNumberInRecord);
}

/**
 * Reads the structure from the current event without copying the event
 * buffer.
 * @param structure - reference to the stucture object
 * @param group - the group is for the structure.
 * @param item  - item id for the structure.
 */
void reader::getStructure(hipo::structure& structure, int group, int item) {
    hipo::data data;
    int eventNumberInRecord = readerEventIndex.getRecordEventNumber();
    inputRecord.getData(data, eventNumberInRecord);
    event::getStructure(data.getDataPtr(), structure, group, item);
}

/**
 * Reads the structure from the current event without copying the event
 * buffer and without copying the structure buffer. This should be used
 * very carefully, since it sets the pointer of the structure directly
 * to the buffer owned by the record. If new record is loaded this
 * structure will be pointing to the wrong part of the buffer.
 * @param structure - reference to the stucture object
 * @param group - the group is for the structure.
 * @param item  - item id for the structure.
 */
void reader::getStructureNoCopy(hipo::structure& structure, int group, int item) {
    hipo::data data;
    int eventNumberInRecord = readerEventIndex.getRecordEventNumber();
    inputRecord.getData(data, eventNumberInRecord);
    event::getStructureNoCopy(data.getDataPtr(), structure, group, item);
}

bool reader::next(std::vector<hipo::bank>& list) {
    if (bool status = next(); status == false)
        return false;

    read(event);

    for (hipo::bank& l : list)
        event.read(l);

    return true;
}

std::vector<hipo::bank> reader::getBanks(const std::vector<std::string>& names) {
    std::vector<hipo::bank> list;
    readDictionary(factory);
    for (const std::string& k : names) {
        hipo::bank b(factory.getSchema(k.c_str()), 48);
        list.push_back(b);
    }
    return list;
}

void reader::readUserConfig(std::map<std::string, std::string>& mapConfig) {

    if (inputStream.is_open() == false) {
        printf("\n\nhipo::reader (ERROR) file is not open.... exiting...\n\n");
        exit(1);
    }
    long position = header.headerLength * 4;
    hipo::record dictRecord;
    dictRecord.readRecord(inputStream, position, 0);
    int nevents = dictRecord.getEventCount();
    /* printf(" reading record at position %8lu, number of entries = %5d\n", 
      position,dictRecord.getEventCount()); */
    hipo::structure sKey;
    hipo::structure sConfig;
    hipo::event event;
    for (int i = 0; i < nevents; i++) {
        dictRecord.readHipoEvent(event, i);
        event.getStructure(sKey, 32555, 1);
        event.getStructure(sConfig, 32555, 2);
        if (sKey.getSize() > 0) {
            mapConfig[std::string(sKey.getStringAt().c_str())] = std::string(sConfig.getStringAt().c_str());
        }
    }
}

/**
 * Reads the dictionary for the file. C++ API is reading packed dictionary
 * format from node (120,2), parses each schema and creates schema dictionary.
 * @param dict - reference to dictionary object.
 */
void reader::readDictionary(hipo::dictionary& dict) {
    if (inputStream.is_open() == false) {
        printf("\n\nhipo::reader (ERROR) file is not open.... exiting...\n\n");
        exit(1);
    }
    long position = header.headerLength * 4;
    hipo::record dictRecord;
    dictRecord.readRecord(inputStream, position, 0);
    int nevents = dictRecord.getEventCount();

    hipo::structure schemaStructure;
    hipo::event dataevent;
    for (int i = 0; i < nevents; i++) {
        dictRecord.readHipoEvent(dataevent, i);
        dataevent.getStructure(schemaStructure, 120, 2);
        dict.parse(schemaStructure.getStringAt().c_str());
    }
}

/**
 * Advances the event pointer to the next event. This does not read an
 * event, but if the event goes beyond boundary of the record the next
 * record is loaded into the memody.
 * @return returns true - if the are events available in the file, false - otherwise
 */
bool reader::next() {
    if (readerEventIndex.canAdvance() == false)
        return false;
    int recordNumber = readerEventIndex.getRecordNumber();
    readerEventIndex.advance();

    if (int recordToBeRead = readerEventIndex.getRecordNumber(); recordToBeRead != recordNumber) {
        long position = readerEventIndex.getPosition(recordToBeRead);
        inputRecord.readRecord(inputStream, position, 0);
    }
    return true;
}

/**
 * Moves the pointer of the event to the event number provided. If the event
 * number is within the same record no reading is done, otherwise the appropriate
 * record is loaded and event indicies are updated.
 * @param eventNumber - number of event to jump to
 * @return true if event is available, false - otherwise
 */
bool reader::gotoEvent(int eventNumber) {
    int recordNumber = readerEventIndex.getRecordNumber();

    //goto event in index if exists, if not return
    if (readerEventIndex.gotoEvent(eventNumber) == false) {
        printf("[WARNING] hipo::reader::gotoEvent event %d greater than max events = %d, will stay at current event\n", eventNumber, readerEventIndex.getMaxEvents());
        return false;
    }

    if (int recordToBeRead = readerEventIndex.getRecordNumber(); recordToBeRead != recordNumber) {
        long position = readerEventIndex.getPosition(recordToBeRead);
        inputRecord.readRecord(inputStream, position, 0);
    }
    return true;
}

/**
 * Moves the current event pointer to the new record # irec. The readerIndex
 * is updated so current event is the first event in loaded record.
 * @param irec - record number to jump to
 * @return true - if the record exists, false - otherwise
 */
bool reader::gotoRecord(int irec) {
    if (bool status = readerEventIndex.gotoRecord(irec); status == false)
        return false;
    long position = readerEventIndex.getPosition(irec);
    inputRecord.readRecord(inputStream, position, 0);
    return true;
}

//dglazier
// Added by Derek - for some reason
// Use gotoRecord instead, since it checks first if record exists.
bool reader::loadRecord(int irec) {
    long position = readerEventIndex.getPosition(irec);
    inputRecord.readRecord(inputStream, position, 0);
    return readerEventIndex.loadRecord(irec);
}

bool reader::loadRecord(hipo::record& record, int irec) {
    long position = readerEventIndex.getPosition(irec);
    record.readRecord(inputStream, position, 0);
    return true;
}

std::vector<int> reader::getInt(const char* bank, const char* column, int max) {
    std::vector<int> rowvec;
    std::vector<hipo::bank> b = getBanks({bank});
    int item = b[0].getSchema().getEntryOrder(column);
    int counter = 0;
    while (next(b) == true) {
        for (int row = 0; row < b[0].getRows(); row++) {
            rowvec.push_back(b[0].getInt(item, row));
            counter++;
        }
        if (max > 0 && counter > max)
            break;
    }
    return rowvec;
}

std::vector<float> reader::getFloat(const char* bank, const char* column, int max) {
    std::vector<float> rowvec;
    std::vector<hipo::bank> b = getBanks({bank});
    int item = b[0].getSchema().getEntryOrder(column);
    int counter = 0;
    while (next(b) == true) {
        for (int row = 0; row < b[0].getRows(); row++) {
            rowvec.push_back(b[0].getFloat(item, row));
            counter++;
        }
        if (max > 0 && counter > max)
            break;
    }
    return rowvec;
}

//dglazier
bool reader::nextInRecord() {
    if (readerEventIndex.canAdvanceInRecord() == false)
        return false;
    readerEventIndex.advance();
    return true;
}

/**
 * Prints out warning if the LZ4 library was not linked to the compiled
 * library. In that case only uncompressed files can be read and written.
 */
void reader::printWarning() const {
#ifndef __LZ4__
    std::cout << "******************************************************" << std::endl;
    std::cout << "* WARNING:                                           *" << std::endl;
    std::cout << "*   This library war compiled without LZ4 support.   *" << std::endl;
    std::cout << "*   Reading and writing compressed buffers will not  *" << std::endl;
    std::cout << "*   work. However un-compressed file I/O will work.  *" << std::endl;
    std::cout << "******************************************************" << std::endl;
#endif
}
}  // namespace hipo

//*****************************************************************************
//* Implementation of reader index class to keep track of events and records
//*****************************************************************************
//--
namespace hipo {
/**
 * Adds record size (number of events) to the list of records.
 */
void readerIndex::addSize(int size) {
    if (recordEvents.empty()) {
        recordEvents.push_back(0);
        recordEvents.push_back(size);
    } else {
        int cz = recordEvents[recordEvents.size() - 1] + size;
        recordEvents.push_back(cz);
    }
}

/**
 * Checks to determine if there are events left in the index buffer
 * @return true - if there are available events, false - otherwise
 */
bool readerIndex::canAdvance() {
    return (currentEvent < getMaxEvents() - 1);
}

/**
 * Advances the event pointer to next. If the next event is in a different
 * record the record number is updated and events number in the record is
 * updated.
 * @return true - if the the next event is available, false - otherwise
 */
bool readerIndex::advance() {
    if (recordEvents.empty())
        return false;
    if (currentEvent + 1 < recordEvents[currentRecord + 1]) {
        currentEvent++;
        currentRecordEvent++;
        return true;
    }
    if (recordEvents.size() < currentRecord + 2 + 1) {
        printf("advance(): Warning, reached the limit of events.\n");
        return false;
    }
    currentEvent++;
    currentRecord++;
    currentRecordEvent = 0;
    return true;
}

/**
 * Moves the event pointer to give event number. The record number and
 * relative event number in the record are recalculated.
 * @param event number to jump to
 * @return true - if event number is valid event, false - otherwise
 */
bool readerIndex::gotoEvent(int eventNumber) {
    //check if event exists
    if (eventNumber >= getMaxEvents())
        return false;
    // The proper record number is found by binary search through records array
    //------
    // G.Gavalian (July 25/2022)
    // Changed the eventNumber -> eventNumber+1 in binary search. Now it changes the
    // record number properly and starts with record event number from 0
    // I think this was a bug.

    auto l_bound = std::lower_bound(recordEvents.begin(), recordEvents.end(), eventNumber + 1);

    std::size_t position = (l_bound - recordEvents.begin()) - 1;
    currentRecord = static_cast<int>(position);
    currentRecordEvent = eventNumber - recordEvents[currentRecord];
    currentEvent = static_cast<int>(l_bound - recordEvents.begin());
    return true;
}

void readerIndex::show() {
    for (int i = 0; i < recordEvents.size(); i++) {
        printf("record = %8d, %8d\n", i, recordEvents[i]);
    }
}

/**
 * Returns maximum number of events available to read.
 * @return maximum number of events.
 */
int readerIndex::getMaxEvents() {
    if (recordEvents.empty())
        return 0;
    return recordEvents[recordEvents.size() - 1];
}

/**
 * Sets the event pointer to the first even of provided record.
 * Originally implemenet by Derek as loadRecord(), I changed the
 * name to keep naming consistent, but left the old one not to break
 * clas12root code.
 * @param irec - the record number to jump to
 * @return true - if the provided record is valid, false - otherwise
 */
bool readerIndex::gotoRecord(int irec) {
    if (irec == 0) {
        currentEvent = -1;
        currentRecord = 0;
        currentRecordEvent = -1;
        return true;
    }
    if (irec + 1 > (int)recordEvents.size())
        return false;
    currentEvent = recordEvents[irec] - 1;
    currentRecord = irec;
    currentRecordEvent = -1;
    return true;
}

//dglazier
/**
* Implemented by Derek for clas12tool purposes (I think - therefore I am)
*/
bool readerIndex::loadRecord(int irec) {
    if (irec == 0) {
        currentEvent = -1;
        currentRecord = 0;
        currentRecordEvent = -1;
        return true;
    }
    if (irec + 1 > (int)recordEvents.size())
        return false;

    currentEvent = recordEvents[irec] - 1;
    currentRecord = irec;
    currentRecordEvent = -1;
    return true;
}

//dglazier
/**
 * Checks to verify if the next event is in the same record as current one.
 * Not sure why Derek needed it ;-), but may be it's useful
 * @return true - if the next event is in the same record, false - otherwise
 */
bool readerIndex::canAdvanceInRecord() {
    return (currentEvent < recordEvents[currentRecord + 1] - 1);
}

}  // namespace hipo
