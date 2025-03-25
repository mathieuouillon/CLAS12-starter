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
/**
 * <pre>
 *
 * FILE HEADER STRUCTURE ( 56 bytes, 14 integers (32 bit) )
 *
 *    +----------------------------------+
 *  1 |              ID                  | HIPO: 0x43455248, Evio: 0x4556494F
 *    +----------------------------------+
 *  2 +          File Number             | split file #
 *    +----------------------------------+
 *  3 +         Header Length            | 14 (words)
 *    +----------------------------------+
 *  4 +      Record (Index) Count        |
 *    +----------------------------------+
 *  5 +      Index Array Length          | bytes
 *    +-----------------------+----------+
 *  6 +       Bit Info        | Version  | version (8 bits)
 *    +-----------------------+----------+
 *  7 +      User Header Length          | bytes
 *    +----------------------------------+
 *  8 +          Magic Number            | 0xc0da0100
 *    +----------------------------------+
 *  9 +          User Register           |
 *    +--                              --+
 * 10 +                                  |
 *    +----------------------------------+
 * 11 +         Trailer Position         | File offset to trailer head (64 bits).
 *    +--                              --+ 0 = no offset available or no trailer exists.
 * 12 +                                  |
 *    +----------------------------------+
 * 13 +          User Integer 1          |
 *    +----------------------------------+
 * 14 +          User Integer 2          |
 *    +----------------------------------+
 *
 * -------------------
 *   Bit Info Word
 * -------------------
 *     0-7  = version
 *     8    = true if dictionary is included (relevant for first record only)
 *     9    = true if this file has "first" event (in every split file)
 *    10    = File trailer with index array exists
 *    11-19 = reserved
 *    20-21 = pad 1
 *    22-23 = pad 2
 *    24-25 = pad 3 (always 0)
 *    26-27 = reserved
 *    28-31 = general header type: 1 = Evio file
 *                                 2 = Evio extended file
 *                                 5 = HIPO file
 *                                 6 = HIPO extended file
 *
 * </pre>
 *
 * @version 6.0
 * @since 6.0 9/6/17
 */
/*
 * File:   reader.h
 * Author: gavalian
 *
 * Created on April 11, 2017, 2:07 PM
 */

#ifndef HIPOREADER_H
#define HIPOREADER_H

#include <climits>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>
#include <utility>
#include <vector>
#include "bank.h"
#include "record.h"
#include "utils.h"

constexpr int HIPO_FILE_HEADER_SIZE = 72;
/* Constants for endianness of the file */
#ifndef BIG_ENDIAN
#define BIG_ENDIAN 0
#endif
#ifndef LITTLE_ENDIAN
#define LITTLE_ENDIAN 1
#endif

namespace hipo {

struct fileHeader_t {
    int uniqueid{};
    int filenumber{};
    int headerLength{};  // in words (usually 14)
    int recordCount{};
    int indexArrayLength{};  // in bytes
    int bitInfo{};
    int version{};
    int userHeaderLength{};
    int magicNumber{};

    long userRegister{};
    long trailerPosition{};
    long firstRecordPosition{};
};

struct recordInfo_t {
    int recordLength{};
    int recordEntries{};

    long recordPosition{};
    long userWordOne{};
    long userWordTwo{};
};

/**
   * READER index class is used to construct entire events
   * sequence from all records, and provides ability to canAdvance
   * through events where record number is automatically calculated
   * and triggers reading of the next record when events in the current
   * record are exhausted.
   */

class readerIndex {

   private:
    std::vector<int> recordEvents;
    std::vector<long> recordPosition;

    int currentRecord{};
    int currentEvent{};
    int currentRecordEvent{};

   public:
    readerIndex() = default;
    ~readerIndex() = default;

    bool canAdvance();
    bool advance();

    //dglazier
    bool canAdvanceInRecord();
    bool loadRecord(int irec);
    bool gotoEvent(int eventNumber);
    bool gotoRecord(int irec);

    int getEventNumber() const { return currentEvent; }

    int getRecordNumber() const { return currentRecord; }

    int getRecordEventNumber() const { return currentRecordEvent; }

    int getMaxEvents();
    void addSize(int size);

    void addPosition(long position) { recordPosition.push_back(position); }

    long getPosition(int index) { return recordPosition[index]; }

    //dglazier
    std::size_t getNRecords() const { return recordEvents.size(); }

    void show();

    void rewind() {
        currentRecord = -1;
        currentEvent = -1;
        currentRecordEvent = -1;
    }

    void clear() {
        recordEvents.clear();
        recordPosition.clear();
    }

    void reset() {
        currentRecord = 0;
        currentEvent = 0;
        currentRecordEvent = 0;
    }

    bool backup() {
        if (recordEvents.empty()) {
            return false;
        }
        if (currentRecord != 0 && currentEvent == recordEvents[currentRecord]) {

            currentEvent--;
            currentRecord--;
            if (currentRecord > 0) {
                currentRecordEvent = recordEvents[currentRecord + 1] - recordEvents[currentRecord] - 1;
            } else {
                currentRecordEvent = currentEvent - 1;
            }
            return true;
        }

        currentEvent--;
        currentRecordEvent--;

        return true;
    }
};

class reader {

   private:
    fileHeader_t header{};
    hipo::utils hipoutils;
    std::ifstream inputStream;
    long inputStreamSize{};

    hipo::record inputRecord;
    hipo::readerIndex readerEventIndex;
    std::vector<long> tagsToRead;

    short _verbose = {0};

    std::map<std::string, std::string> userConfig;

    hipo::event event;
    hipo::dictionary factory;

    void readHeader();
    void readIndex();

   public:
    reader();

    explicit reader(const char* file) { open(file); }

    explicit reader(const std::string_view file, hipo::dictionary& dict, const short verbose = 0);

    reader(const char* file, const std::vector<int>& tags) {
        for (int tag : tags)
            setTags(tag);
        open(file);
    }

    reader(const reader& r) = delete;

    ~reader();

    void about() const;

    void rewind() { readerEventIndex.rewind(); }

    void readDictionary(hipo::dictionary& dict);
    void getStructure(hipo::structure& structure, int group, int item);
    void getStructureNoCopy(hipo::structure& structure, int group, int item);

    void readUserConfig(std::map<std::string, std::string>& mapConfig);

    void open(const char* filename);

    bool is_open() { return inputStream.is_open(); }

    void setTags(int tag) { tagsToRead.push_back(tag); }

    void setTags(std::vector<long> tags) { tagsToRead = std::move(tags); }

    void setVerbose(short level = 1) { _verbose = level; }

    bool hasNext();
    bool next();
    bool gotoEvent(int eventNumber);
    bool gotoRecord(int irec);
    bool next(hipo::event& dataevent);

    bool next(std::vector<hipo::bank>& list);
    std::vector<hipo::bank> getBanks(const std::vector<std::string>& names);

    void read(hipo::event& dataevent);
    void printWarning() const;

    std::size_t getNRecords() const { return readerEventIndex.getNRecords() - 1; }

    bool nextInRecord();
    bool loadRecord(int irec);
    bool loadRecord(hipo::record& record, int irec);

    int getEntries() { return readerEventIndex.getMaxEvents(); }

    std::vector<int> getInt(const char* bank, const char* column, int max = -1);
    std::vector<float> getFloat(const char* bank, const char* column, int max = -1);

    template <typename... Args>
    auto for_each_arg(hipo::event& dataevent, Args&... args) -> void {
        (dataevent.getStructure(args), ...);
    }

    /**
     * Advances the event index and reads the next event from the input record.
     *
     * @param dataevent the event to be read
     * @param args      banks to be fill
     *
     * @return true if the event was read successfully, false otherwise
     */
    template <typename... Args, typename = std::enable_if_t<(std::is_same_v<Args, hipo::bank> && ...)>>
    auto next(hipo::event& dataevent, Args&... args) -> bool {
        if (readerEventIndex.canAdvance() == false) return false;
        int recordNumber = readerEventIndex.getRecordNumber();
        readerEventIndex.advance();

        if (int recordToBeRead = readerEventIndex.getRecordNumber(); recordToBeRead != recordNumber) {
            long position = readerEventIndex.getPosition(recordToBeRead);
            inputRecord.readRecord(inputStream, position, 0);
        }

        int eventNumberInRecord = readerEventIndex.getRecordEventNumber();
        inputRecord.readHipoEvent(dataevent, eventNumberInRecord);

        for_each_arg(dataevent, args...);

        return true;
    }

    int eventNumber() const { return readerEventIndex.getEventNumber(); }

    template <typename... Args, typename = std::enable_if_t<(std::is_same_v<Args, hipo::bank> && ...)>>
    auto previous(hipo::event& dataevent, Args&... args) -> bool {
        //if (readerEventIndex.canBackup() == false) return false;
        int recordNumber = readerEventIndex.getRecordNumber();
        readerEventIndex.backup();

        if (int recordToBeRead = readerEventIndex.getRecordNumber(); recordToBeRead != recordNumber) {
            long position = readerEventIndex.getPosition(recordToBeRead);
            inputRecord.readRecord(inputStream, position, 0);
        }

        int eventNumberInRecord = readerEventIndex.getRecordEventNumber();
        inputRecord.readHipoEvent(dataevent, eventNumberInRecord);

        for_each_arg(dataevent, args...);

        return true;
    }
};

class readerstream {
   private:
    hipo::reader hr;
    hipo::dictionary factory;
    std::mutex obj;
    long nProcessed = 0;
    long nDataLimit = -1;

   public:
    readerstream() = default;

    virtual ~readerstream() = default;

    void open(const char* input) {
        hr.open(input);
        hr.readDictionary(factory);
    }

    void setLimit(long limit) {
        nDataLimit = limit;
    }

    void run(std::function<int(int)>&& function, int nthreads) {
        std::vector<std::thread> threads;
        for (int i = 0; i < nthreads; i++) {
            threads.push_back(std::thread(function, i));
        }
        printf("-- created denoiser with %lu threads\n", threads.size());
        for (std::thread& thread : threads)
            thread.join();
    }

    hipo::reader& reader() { return hr; }

    hipo::dictionary& dictionary() { return factory; }

    void pull(std::vector<hipo::event>& events) {

        std::unique_lock<std::mutex> lock(obj);
        bool finished = false;
        if (nDataLimit > 0) {
            if (nProcessed > nDataLimit)
                finished = true;
        }

        if (hr.hasNext() == false) {
            printf("\n");
        }

        for (int n = 0; n < (int)events.size(); n++) {
            // write the event in the output if it's not empty
            //if(events[n].getSize()>16){ hw.addEvent(events[n]);}
            // reset event and read next in the file if any left
            events[n].reset();
            if (hr.next() == true && finished == false) {
                hr.read(events[n]);
                nProcessed++;
                if (nProcessed % 250 == 0) {
                    printf(".");
                    fflush(stdout);
                }
                if (nProcessed % 10000 == 0)
                    printf(" : %9lu \n", nProcessed);
            }
        }
    }
};

}  // namespace hipo
#endif /* HIPOREADER_H */
