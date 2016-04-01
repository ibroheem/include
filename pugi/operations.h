#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <vector>

#include "mib/io.h"
#include "pugi/pugixml.hpp"

using namespace pugi;
using namespace mvc_utils::io;
using namespace std;

namespace pugi_operations
{

   inline xml_node append_child (xml_node & node, cchar* name)
   {
      return node.append_child (name);
   }
#ifdef QSTRING_H
   inline xml_node append_child (xml_node & node, const QString& name)
   {
      return append_child (node, static_cast<cchar *> (name.toUtf8() ) );
   }
#endif // QSTRING_H
   xml_node append_child (xml_node & node, cchar* name, cchar* value)
   {
      auto tmp = node.append_child (name);
      if (value)
         tmp.append_child (pugi::node_pcdata).set_value (value);
      return tmp;
   }
#ifdef QSTRING_H
   xml_node append_child (xml_node & node, const QString & name, const QString & value)
   {
      return append_child ( node, static_cast<cchar *> (name.toUtf8() ), static_cast<cchar *> (value.toUtf8() ) );
   }
#endif // QSTRING_H
   template <class T_name, class T_Value>
   xml_node append_children (xml_node & node, T_name &&name, T_Value &&value)
   {
      auto it_name = name.begin();
      auto it_value = value.begin();
      while (it_name != name.end() )
      {
         append_child (node, * (it_name++), * (it_value++) );
      }
      return node;
   }

   template <class T_name, class T_Value>
   xml_node append_children (xml_node & node, const T_name &name, const T_Value &value)
   {
      return append_children (node, std::forward < T_name && > (name), std::forward < T_Value && > (value) );
   }

   void append_attribute (xml_node & node, cchar* name, cchar* value)
   {
      if (value)
         node.append_attribute (name).set_value (value);
   }

   void append_attribute (xml_node & node, c_string &name, c_string &value)
   {
      if (value.c_str())
         node.append_attribute (name.c_str()).set_value (value.c_str());
   }
#ifdef QSTRING_H
   void append_attribute (xml_node & node, const QString & name, const QString & value)
   {
      append_attribute ( node, static_cast<cchar *> (name.toUtf8() ), static_cast<cchar *> (value.toUtf8() ) );
   }

   void append_attribute (xml_node & node, const char* name, const QByteArray & value)
   {
      append_attribute ( node, name, static_cast<cchar *> (value) );
   }
#endif // QSTRING_H
   template <class T_name, class T_Value>
   xml_node append_attributes (xml_node & node, initializer_list<T_name> &&name,
         initializer_list<T_Value> &&value)
   {
      auto it_name = name.begin();
      auto it_value = value.begin();
      while (it_name != name.end() )
      {
         append_attribute (node, * (it_name++), * (it_value++) );
      }
      return node;
   }


   void operations_usage()
   {

      /* using namespace write;
       xml_document doc;

       xml_node nd = doc.append_child ("header");
       vector<cchar*> vn = {};

       vn.push_back ("column");
       vn.push_back ("row");

       append_children (nd, vn, vn);
       append_children (nd, vn, {"1", "2"});
       append_attributes (nd, vn,  {"1", "2"});

       doc.save_file ("test.xml");*/
   }

   namespace read
   {
      namespace traverse_iter
      {
         enum class return_type_ctrl { attribute, value };

         template <typename Attribute_Type = string>
         vector< Attribute_Type > attributes_or_values(const xml_node & _node, return_type_ctrl rtc)
         {
            vector<Attribute_Type> &&vec_attr = {};

            switch (rtc)
            {
               case return_type_ctrl::attribute:
               {
                  for (xml_node node : _node.children() )
                     for (xml_attribute attr : _node.attributes() )
                        vec_attr.push_back (attr.name() );
               } break;

               case return_type_ctrl::value:
               {
                  for (xml_node node : _node.children() )
                     for (xml_attribute attr : _node.attributes() )
                        vec_attr.push_back (attr.value() );
               } break;
            }
            return std::move(vec_attr);
         }

         /**
           Iterates a given node attribute
           Returns vector< pair<Attribute_Type, Value_Type> > holding both attribute and value
         */
         template <typename Attribute_Type = string, typename Value_Type = string>
         auto attributes_n_values(const xml_node & _node)
#if __cplusplus < 201402L
         -> vector < pair<Attribute_Type, Value_Type> >
#endif
         {
            vector< pair<Attribute_Type, Value_Type> > vec_attr;
            for (xml_attribute attr : _node.attributes())
               vec_attr.push_back({attr.name(), attr.value()});

            return std::move(vec_attr);
         }

         /**
           Iterates a given node childeren then their attribute, for each child iterate its attributes
           Returns vector< pair<Attribute_Type, Value_Type> > holding both attribute and value
         */
         template <typename Pair_Type = pair<const char*, const char*> >
         vector<Pair_Type>  attributes_n_values_iterate_node(const xml_node & _node)
         {
            vector<Pair_Type> vec_attr;

            for (xml_node node : _node.children())
               for (xml_attribute attr : node.attributes())
                  vec_attr.push_back({attr.name(), attr.value()});

            return std::move(vec_attr);
         }
      }

      void usage(uint opt)
      {
         using namespace pugi_operations::read::traverse_iter;
         switch (opt)
         {
            case 1:
            {
               xml_document doc;
               if (!doc.load_file ("xml/xgconsole.xml"))
                  return;

               xml_node tools = doc.child ("Profile").child ("Tools").child("Tool");
               xml_node tools2 = doc.child ("Profile").child ("Tools");

               vector<pair<string, string>> &&v = attributes_n_values(tools);
               auto v2 = attributes_n_values_iterate_node(tools2);

               for (uint i = 0; i != v.size(); ++i)
               {
                  print_w_tab_ln(v[i].first, v[i].second);
               }
            } break;

            case 2:
            {
               xml_document doc;
               string &&s = "tit";

               if (!doc.load_file ("Book10.xml"))
                  return;

               xml_node tools2 = doc.child ("header").find_child_by_attribute("table", "name", "t");

               for (xml_node node : tools2.children())
               {
                  for (xml_attribute attr : node.attributes())
                  {
                     if (s == attr.name())
                        print_w_tab_ln(attr.name(), attr.value());
                  }
               }
            } break;

            case 3:
            {

            } break;

            default:
               break;
         }

      }
   }

}


#endif//OPERATIONS_H
