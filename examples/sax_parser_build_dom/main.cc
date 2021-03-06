// -*- C++ -*-

/* main.cc
 *
 * By Dan Dennedy <dan@dennedy.org> 
 *
 * Copyright (C) 2003 The libxml++ development team
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <fstream>
#include <iostream>

#include "svgparser.h"
#include "svgdocument.h"
#include "svgelement.h"
#include "svgpath.h"
#include "svggroup.h"

int
main(int argc, char* argv[])
{
  // Set the global C and C++ locale to the user-configured locale,
  // so we can use std::cout with UTF-8, via xmlpp::string, without exceptions.
  std::locale::global(std::locale(""));

  std::string filepath;
  if(argc > 1 )
    filepath = argv[1]; //Allow the user to specify a different XML file to parse.
  else
    filepath = "example.xml";

  #ifdef LIBXMLCPP_EXCEPTIONS_ENABLED
  try
  {
  #endif //LIBXMLCPP_EXCEPTIONS_ENABLED
    SVG::Document doc;
    SVG::Parser parser(doc);

    // Parse from XML:
    parser.parse_file(filepath);

    // Serialize the custom DOM as XML
    std::cout << doc.write_to_string_formatted() << std::endl;

    // Use the custom DOM
    SVG::Element* element = doc.get_root();
    std::cout << "root's name is \"" << element->get_name() << "\"" << std::endl;
    xmlpp::NodeSet nl = element->find("//path[@style != '']");
    if(!nl.empty())
    {
      SVG::Path* path = dynamic_cast<SVG::Path*>(nl[0]);
      std::cout << "style of first path node with a style = \"" << path->get_style() << "\"" << std::endl;
    }
  #ifdef LIBXMLCPP_EXCEPTIONS_ENABLED
  }
  catch(const xmlpp::exception& ex)
  {
    std::cout << "libxml++ exception: " << ex.what() << std::endl;
  }
  #endif //LIBXMLCPP_EXCEPTIONS_ENABLED
  
  return 0;
}

