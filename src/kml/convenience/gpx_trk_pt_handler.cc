// Copyright 2009, Google Inc. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//  1. Redistributions of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//  2. Redistributions in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//  3. Neither the name of Google Inc. nor the names of its contributors may be
//     used to endorse or promote products derived from this software without
//     specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
// EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// This file contains the implementation of the GoogleSpreadsheets class.

#include "kml/convenience/gpx_trk_pt_handler.h"

namespace kmlconvenience {

void GpxTrkPtHandler::StartElement(const std::__cxx11::string& name, const std::vector< std::__cxx11::string >& atts){
   if (name.compare("trkpt") == 0) {
     // <trkpt lat="-33.911973070" lon="18.422974152">
     // If both lat and lon exist and are sane doubles create a Vec3 for
     // the point.
     std::unique_ptr<kmlbase::Attributes> attributes(
         kmlbase::Attributes::Create(atts));
     if (attributes.get()) {
       double latitude;
       double longitude;
       if (attributes->GetDouble("lat", &latitude) &&
           attributes->GetDouble("lon", &longitude)) {
         vec3_.reset(new kmlbase::Vec3(longitude, latitude));
       }
     }
     time_.clear();
   } else if (name.compare("time") == 0  ||
              name.compare("ele") == 0) {
     // <time>2008-10-11T14:55:41Z</time>
     // <ele>4.943848</ele>
     gather_char_data_ = true;
     char_data_.clear();
   }
 }

void GpxTrkPtHandler::EndElement(const std::__cxx11::string& name){
   if (name.compare("trkpt") == 0) {
     // </trkpt>
     // If a Vec3 was created for this element call the handler.
     if (vec3_.get()) {
       HandlePoint(*vec3_, time_);
     }
   } else if (name.compare("time") == 0) {
     // <time>2008-10-11T14:55:41Z</time>
     time_ = char_data_;
   } else if (name.compare("ele") == 0) {
     // <ele>4.943848</ele>
     if (vec3_.get()) {
       vec3_->set_altitude(kml_strtod(char_data_.c_str(), NULL));
     }
   }
 }

void GpxTrkPtHandler::CharData(const std::__cxx11::string& str){
   if (gather_char_data_) {
     char_data_.append(str);
   }
 }

void GpxTrkPtHandler::HandlePoint(const kmlbase::Vec3& where, const std::__cxx11::string& when){
 }
}  // end namespace kmlconvenience
