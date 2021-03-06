/*
 *  SeismicTraces : another C++ library that reads files in SEG-Y format
 * 
 *  Copyright (C) 2014  Massimiliano Culpo
 * 
 *  This file is part of SeismicTraces.
 *
 *  SeismicTraces is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  SeismicTraces is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 * 
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with SeismicTraces.  If not, see <http://www.gnu.org/licenses/>.
 */

#include<SegyFile.h>
#include<example_macro.h>

#include<vector>
#include<iostream>

#include<impl/rev1/SegyFile-Fields-Rev1.h>

using namespace seismic;
using namespace seismic::constants;
using namespace std;

int main() {
    
    { // The scope is just needed to close SEG Y files in this simple example
        
        //
        // Open input SEG Y file in read mode
        //
        SegyFile segyFile(DATA_FOLDER "/l10f1.sgy", "Rev1");

        cout << segyFile.getBinaryFileHeader() << endl;

        //
        // Read all the samples and convert the traces to a more manageable format
        //
        cout << "Number of traces : " << segyFile.ntraces() << endl;

        vector< SegyFile::raw_trace_type > segyTraces;
        for (size_t ii = 0; ii < segyFile.ntraces(); ++ii) {
            segyTraces.push_back(segyFile.readRawTrace(ii));
            if (ii % 1000 == 0) {
                cout << segyTraces[ii].first << endl;
            }
        }

        //
        // Copying a SEG Y file
        //
        SegyFile segyOutputFile(DATA_FOLDER "/dummy.segy", "Rev1","InFile");

        segyOutputFile.getTextualFileHeader() = segyFile.getTextualFileHeader();
        segyOutputFile.getBinaryFileHeader() = segyFile.getBinaryFileHeader();
        segyOutputFile.commitFileHeaderModifications(); // Write to file
        for (size_t ii = 0; ii < segyFile.ntraces(); ++ii) {
            // Each trace may be manipulated here
            segyOutputFile.appendRawTrace(segyFile.readRawTrace(ii));
        }
        segyOutputFile.commitTraceModifications(); // Write to file 

        cout << "Number of traces " << segyOutputFile.ntraces() << endl;

        //
        // Modify a couple of traces
        //

        auto trace = segyOutputFile.readRawTrace(5);
        trace.first[rev1::th::sourceCoordinateX] = 10;
        segyOutputFile.overwriteRawTrace(trace, 5);

        trace = segyOutputFile.readRawTrace(11);
        trace.first[rev1::th::sourceCoordinateY] = 11;
        segyOutputFile.overwriteRawTrace(trace, 11);

        segyOutputFile.commitTraceModifications(); // Write to file 

        trace = segyOutputFile.readRawTrace(5);
        if (trace.first[rev1::th::sourceCoordinateX] != 10) {
            cout << "Something went wrong" << endl;
        }

        cout << "Number of traces " << segyOutputFile.ntraces() << endl;
    }
    
    remove(DATA_FOLDER "/dummy.segy");
    return 0;
}

