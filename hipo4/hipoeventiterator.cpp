#include "hipoeventiterator.h"

namespace hipo {

// hipoeventfile::begin() and end() implementations
hipoeventfile::iterator hipoeventfile::begin() {
    reader.rewind();  // reset to start of file (if already read, rewind index)
    return iterator(&reader, &dict);
}

hipoeventfile::iterator hipoeventfile::end() {
    return iterator();  // default (at_end=true) indicates end-of-stream
}

// hipoeventfile::iterator private constructor
hipoeventfile::iterator::iterator(hipo::reader* rdr, hipo::dictionary* dict)
    : reader_ptr(rdr), dict_ptr(dict), at_end(false) {
    // Advance to the first event
    if (!reader_ptr || !reader_ptr->next(current_event)) {
        // No event available (empty file or error)
        reader_ptr = nullptr;
        dict_ptr = nullptr;
        at_end = true;
    } else {
        // Successfully read first event; initialize wrapper
        current_wrap = hipoevent(&current_event, dict_ptr);
    }
}

// Pre-increment operator: move to next event in the file
hipoeventfile::iterator& hipoeventfile::iterator::operator++() {
    if (!reader_ptr || at_end) {
        // already at end, do nothing
        return *this;
    }
    // Attempt to read the next event
    if (!reader_ptr->next(current_event)) {
        // No more events -> mark as end
        reader_ptr = nullptr;
        dict_ptr = nullptr;
        at_end = true;
    } else {
        // Loaded next event successfully, update the wrapper
        current_wrap = hipoevent(&current_event, dict_ptr);
    }
    return *this;
}

// Inequality comparison
bool hipoeventfile::iterator::operator!=(const hipoeventfile::iterator& other) const {
    // Two iterators are not equal if one is at end and the other is not.
    bool thisEnd = at_end;
    bool otherEnd = other.at_end;
    if (thisEnd && otherEnd) {
        return false;  // both at end (equal)
    }
    return !(thisEnd && otherEnd);  // not equal if one is end and the other is not
}

}  // namespace hipo
