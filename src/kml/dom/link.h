// Copyright 2008, Google Inc. All rights reserved.
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

// This file contains the declarations for the the classes for the Link, Icon,
// and Url elements.

#ifndef KML_DOM_LINK_H__
#define KML_DOM_LINK_H__

#include "kml/config.h"
#include "kml/dom/kml22.h"
#include "kml/dom/object.h"

namespace kmldom {

class Visitor;

// OGC KML 2.2 Standard: 12.9 kml:Icon (kml:BasicLinkType)
// OGC KML 2.2 XSD: <complexType name="BasicLinkType"...
class KML_EXPORT BasicLink : public Object {
 public:
  virtual ~BasicLink();
  virtual KmlDomType Type() const;
  virtual bool IsA(KmlDomType type) const;

  // <href>
  const string& get_href() const;
  bool has_href() const;
  void set_href(const string& href);
  void clear_href();

  // Visitor API methods, see visitor.h.
  virtual void Accept(Visitor* visitor);

 protected:
  // Internal class, not for direct instantiation.
  BasicLink();
  virtual void AddElement(const ElementPtr& element);
  virtual void Serialize(Serializer& serializer) const;

 private:
  string href_;
  bool has_href_;
  LIBKML_DISALLOW_EVIL_CONSTRUCTORS(BasicLink);
};

// This is LinkType in the KML 2.2 XSD.  LinkType is the only XSD complexType
// instantiated as more than one element.
class KML_EXPORT AbstractLink : public BasicLink {
 public:
  virtual ~AbstractLink();

  // <refreshMode>
  int get_refreshmode() const;
  bool has_refreshmode() const;
  void set_refreshmode(const int refreshmode);
  void clear_refreshmode();

  // <refreshInterval>
  double get_refreshinterval() const;
  bool has_refreshinterval() const;
  void set_refreshinterval(const double refreshinterval);
  void clear_refreshinterval();

  // <viewRefreshMode>
  int get_viewrefreshmode() const;
  bool has_viewrefreshmode() const;
  void set_viewrefreshmode(const int viewrefreshmode);
  void clear_viewrefreshmode();

  // <viewRefreshTime>
  double get_viewrefreshtime() const;
  bool has_viewrefreshtime() const;
  void set_viewrefreshtime(const double viewrefreshtime);
  void clear_viewrefreshtime();

  // <viewBoundScale>
  double get_viewboundscale() const;
  bool has_viewboundscale() const;
  void set_viewboundscale(const double viewboundscale);
  void clear_viewboundscale();

  // <viewFormat>
  const string& get_viewformat() const;
  bool has_viewformat() const;
  void set_viewformat(const string& viewformat);
  void clear_viewformat();

  // <httpQuery>
  const string& get_httpquery() const;
  bool has_httpquery() const;
  void set_httpquery(const string& httpquery);
  void clear_httpquery();

 protected:
  // Internal class, not for direct instantiation.
  AbstractLink();
  virtual void AddElement(const ElementPtr& element);
  virtual void Serialize(Serializer& serializer) const;

 private:
  bool has_href_;
  int refreshmode_;
  bool has_refreshmode_;
  double refreshinterval_;
  bool has_refreshinterval_;
  int viewrefreshmode_;
  bool has_viewrefreshmode_;
  double viewrefreshtime_;
  bool has_viewrefreshtime_;
  double viewboundscale_;
  bool has_viewboundscale_;
  string viewformat_;
  bool has_viewformat_;
  string httpquery_;
  bool has_httpquery_;
  LIBKML_DISALLOW_EVIL_CONSTRUCTORS(AbstractLink);
};

// <Link> in NetworkLink and Model
class KML_EXPORT Link : public AbstractLink {
 public:
  virtual ~Link();
  virtual KmlDomType Type() const;
  virtual bool IsA(KmlDomType type) const;

  // Visitor API methods, see visitor.h.
  virtual void Accept(Visitor* visitor);

 private:
  friend class KmlFactory;
  Link();
  LIBKML_DISALLOW_EVIL_CONSTRUCTORS(Link);
};

// <Icon> in Overlay
class KML_EXPORT Icon : public AbstractLink {
 public:
  virtual ~Icon();
  virtual KmlDomType Type() const;
  virtual bool IsA(KmlDomType type) const;

  // Visitor API methods, see visitor.h.
  virtual void Accept(Visitor* visitor);

 private:
  friend class KmlFactory;
  Icon();
  LIBKML_DISALLOW_EVIL_CONSTRUCTORS(Icon);
};

// <Url> in NetworkLink
class KML_EXPORT Url : public AbstractLink {
 public:
  virtual ~Url();
  virtual KmlDomType Type() const;
  virtual bool IsA(KmlDomType type) const;

  // Visitor API methods, see visitor.h.
  virtual void Accept(Visitor* visitor);

 private:
  friend class KmlFactory;
  Url();
  LIBKML_DISALLOW_EVIL_CONSTRUCTORS(Url);
};

// <Icon> in <IconStyle>
// This is the only case in KML of a non-global element.  The <Icon>
// of any Overlay is the same as <Link> with all refresh modes, etc.
// The <Icon> of <IconStyle> is just an <href> to an icon as the
// derivation from BasicLink suggests.
class KML_EXPORT IconStyleIcon : public BasicLink {
 public:
  virtual ~IconStyleIcon();
  virtual KmlDomType Type() const;
  virtual bool IsA(KmlDomType type) const;

  // <gx:x>
  double get_gx_x() const;
  bool has_gx_x() const;
  void set_gx_x(const double x);
  void clear_gx_x();

  // <gx:y>
  double get_gx_y() const;
  bool has_gx_y() const;
  void set_gx_y(const double y);
  void clear_gx_y();

  // <gx:w>
  double get_gx_w() const;
  bool has_gx_w() const;
  void set_gx_w(const double w);
  void clear_gx_w();

  // <gx:h>
  double get_gx_h() const;
  bool has_gx_h() const;
  void set_gx_h(const double h);
  void clear_gx_h();

  virtual void AddElement(const ElementPtr& element);

  // Visitor API methods, see visitor.h.
  virtual void Accept(Visitor* visitor);

 private:
  friend class KmlFactory;
  IconStyleIcon();
  friend class Serializer;
  virtual void Serialize(Serializer& serializer) const;
  double gx_x_;
  bool has_gx_x_;
  double gx_y_;
  bool has_gx_y_;
  double gx_w_;
  bool has_gx_w_;
  double gx_h_;
  bool has_gx_h_;
  LIBKML_DISALLOW_EVIL_CONSTRUCTORS(IconStyleIcon);
};

}  // end namespace kmldom

#endif  // KML_DOM_LINK_H__
