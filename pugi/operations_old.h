#ifndef HEADER_30E69B0EC53C9F1
#define HEADER_30E69B0EC53C9F1


#include <mib/macros.h>
#include <mib/typedefs.h>

using namespace pugi;
using namespace std;

/** Adds an attribute { with @name and optional @value} to a node */
inline void append_attribute(xml_node &node, c_ref_string name, c_ref_string value = "")
{
  node.append_attribute(name.c_str()).set_value(value.c_str());
}

/** Adds  attribute {with @name and optional @value} to a node  */
inline void append_attribute(xml_node &node, c_ref_string name, const QByteArray& value)
{
  node.append_attribute(name.c_str()).set_value(static_cast<cchar*>(value));
}

template <typename Value_T>
inline void append_attribute(xml_node &node, c_ref_string name, Value_T value)
{
  node.append_attribute(name.c_str()).set_value(value);
}

/** Adds attributes {with @names and @value} to a node */
template <typename Value_T>
inline void append_attributes(xml_node &node, init_list<string> &&name, init_list<Value_T> &&value)
{
  auto bname = name.begin();
  auto bvalue = value.begin();
  for (; bname != name.end(); ++bname, ++bvalue)
  {
    if (Typename(Value_T) != Typename(string))
      node.append_attribute(bname->c_str()).set_value(*bvalue);
  }
}

/** Adds attributes {with @names and @value} to a node */
template <typename Value_T>
inline void append_attributes(xml_node &node, init_list<string> &name, init_list<Value_T> &value)
{
  std::forward<xml_node, string, Value_T>(node, name, value);
}

/** Adds attributes {with @names and @value} to a node */
inline void append_attributes_Qt(xml_node &node, init_list<string> &&name, init_list<QByteArray> &&value)
{
  auto bname = name.begin();
  auto bvalue = value.begin();
  for (; bname != name.end(); ++bname, ++bvalue)
  {
    node.append_attribute(bname->c_str()).set_value(static_cast<cchar*>(*bvalue));
  }
}

inline void append_attributes_Qt(xml_node &node, init_list<string> &&name, QList<QByteArray> &value)
{
  auto bname = name.begin();
  auto bvalue = value.begin();
  for (; bname != name.end(); ++bname, ++bvalue)
  {
    node.append_attribute(bname->c_str()).set_value(static_cast<cchar*>(*bvalue));
  }
}

inline void append_attributes_Qt(xml_node &node, init_list<string> &name, QList<QByteArray> &value)
{
  auto bname = name.begin();
  auto bvalue = value.begin();
  for (; bname != name.end(); ++bname, ++bvalue)
  {
    node.append_attribute(bname->c_str()).set_value(static_cast<cchar*>(*bvalue));
  }
}

inline xml_node append_child(xml_node &node, c_ref_string name)
{
  auto tmp = node.append_child(name.c_str());
  return tmp;
}

inline xml_node append_child(xml_node &node, c_ref_string name, c_ref_string value)
{
  auto tmp = node.append_child(name.c_str());
  if (!value.empty())
    tmp.append_child(pugi::node_pcdata).set_value(value.c_str());
  return tmp;
}

inline xml_node append_child(xml_node &node, xml_node_type name, cchar* value = "")
{
  auto tmp_node = node.append_child(name);
  tmp_node.set_value(value);
  return tmp_node;
}

inline xml_node append_child(xml_node &node, xml_node_type name, c_ref_string value = "")
{
  return append_child(node, name, value.c_str());
}

template <typename Value_T>
inline xml_node append_children(xml_node &node, initializer_list<cchar*> &&element_name,
                                std::initializer_list<Value_T> &&value = "")
{
  auto b_element_name = element_name.begin();
  auto bvalue = value.begin();
  for (; b_element_name != element_name.end(); ++b_element_name, ++bvalue)
  {
    if (Typename(Value_T) == Typename(string))
      node.append_child(*b_element_name).set_value(*bvalue);

    else if (Typename(Value_T) == Typename(const char*))
      node.append_child(*b_element_name).set_value(*bvalue);
  }
  return node;
}

/** :Defective In Operation */
template <typename Value_T>
inline xml_node append_children(xml_node &node, initializer_list<xml_node_type> &&element_type,
                                initializer_list<Value_T> &&value = "")
{
  auto b_element_type = element_type.begin();
  auto bvalue = value.begin();
  for (; b_element_type != element_type.end(); ++b_element_type, ++bvalue)
  {
    if (Typename(Value_T) != Typename(string))
      node.append_child(*b_element_type).set_value(*bvalue);

    else if (Typename(Value_T) == Typename(cchar*))
      node.append_child(*b_element_type).set_value(*bvalue);
  }
  return node;
}

template <typename Value_T>
inline xml_node append_children(xml_node &node, initializer_list<xml_node_type> &&element_type,
                                QList<Value_T> &value = "")
{
  auto b_element_type = element_type.begin();
  auto bvalue = value.begin();
  for (; b_element_type != element_type.end(); ++b_element_type, ++bvalue)
  {
    node.append_child(*b_element_type).set_value(static_cast<cchar*>(*bvalue));
  }
  return node;
}

template <typename Value_T>
inline xml_node append_children(xml_node &node, initializer_list<cchar*> &&element_name, QList<Value_T> &value = "")
{
  auto b_element_name = element_name.begin();
  auto bvalue = value.begin();
  for (; b_element_name != element_name.end(); ++b_element_name, ++bvalue)
  {
    node.append_child(*b_element_name).set_value(static_cast<cchar*>(*bvalue));
  }
  return node;
}

#endif // header guard
