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

/**
 * @file SegyFile-BinaryFileHeader-Rev0.h
 * @brief Binary file header revision 0
 */
#ifndef SEGYFILE_BINARYFILEHEADER_REV0_H
#define	SEGYFILE_BINARYFILEHEADER_REV0_H

#include<impl/SegyFile-BinaryFileHeader.h>
#include<impl/rev0/SegyFile-Fields-Rev0.h>

#include<vector>

namespace seismic {

    /**
     * @brief Models the Binary file header of a REV 0 SEGY file
     * 
     * According to SEGY rev 1 standard (May 2002):
     * 
     * > The 400-byte Binary File Header record contains binary values that 
     * > affect the whole SEG Y file.  The values in the Binary File Header 
     * > are defined as two-byte or four-byte, two's complement integers.  
     * > Certain values in this header are crucial for the processing of the 
     * > data in the file, particularly the sampling interval, trace length and
     * > format code.  This revision defines a few additional fields in the 
     * > optional portion, as well as providing some clarification on the use 
     * > of some existing entries.
     * 
     * The following is a small example of the basic use of the class:
     * @include example03.cpp
     */
    template<>
    class ConcreteBinaryFileHeader<Rev0> : public BinaryFileHeader {
    public:
        /// Add a create method that 
        FACTORY_ADD_CREATE(ConcreteBinaryFileHeader<Rev0>)
        
        /* virtual */
        void print(std::ostream& cout) const override;
        /* virtual */
        void invertByteOrder();
        /* virtual */
        void checkConsistencyOrThrow() const override;        
        
    private:
        /**
         * @brief Returns a reference to a static vector used to 
         * iterate over all the int32_t fields of the stream
         * 
         * @return reference to a static constant vector
         */
        const std::vector< Int32Field >& Int32List();        
        
        /**
         * @brief Returns a reference to a static vector used to 
         * iterate over all the int16_t fields of the stream
         * 
         * @return reference to a static constant vector
         */
        const std::vector< Int16Field >& Int16List();

        /**
         * @brief Field needed to register the class into its factory
         */
        static const bool isRegistered;
    };

}

#endif	/* SEGYFILE_BINARYFILEHEADER_REV0_H */

