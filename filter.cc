// filter.cc
#include "filter.h"
#include "filter-element.h"
#include "ns3/log.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("Filter");
NS_OBJECT_ENSURE_REGISTERED (Filter);

TypeId
Filter::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::Filter")
    .SetParent<Object> ()
    .SetGroupName ("Network")
    .AddConstructor<Filter> ()
  ;
  return tid;
}

Filter::Filter () :
  m_elements ()
{
  NS_LOG_FUNCTION (this);
}

Filter::~Filter ()
{
  NS_LOG_FUNCTION (this);
}

void
Filter::DoDispose (void)
{
  NS_LOG_FUNCTION (this);
  m_elements.clear ();
  Object::DoDispose ();
}

bool
Filter::Match (Ptr<Packet> p)
{
  NS_LOG_FUNCTION (this << p);
  
  // If no elements, always match
  if (m_elements.empty ())
    {
      NS_LOG_LOGIC ("No elements, default match");
      return true;
    }
  
  // Check if the packet matches all elements (AND operation)
  for (uint32_t i = 0; i < m_elements.size (); i++)
    {
      if (!m_elements[i]->Match (p))
        {
          NS_LOG_LOGIC ("Packet doesn't match element " << i);
          return false;
        }
    }
  
  NS_LOG_LOGIC ("Packet matches all elements");
  return true;
}

void
Filter::AddFilterElement (Ptr<FilterElement> element)
{
  NS_LOG_FUNCTION (this << element);
  m_elements.push_back (element);
}

} // namespace ns3

