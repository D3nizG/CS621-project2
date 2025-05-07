// tos-field.cc
#include "tos-field.h"
#include "ns3/log.h"
#include "ns3/ipv4-header.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("TosField");
NS_OBJECT_ENSURE_REGISTERED (TosField);

TypeId
TosField::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::TosField")
    .SetParent<FilterElement> ()
    .SetGroupName ("Network")
    .AddConstructor<TosField> ()
  ;
  return tid;
}

TosField::TosField () :
  m_tos (0)
{
  NS_LOG_FUNCTION (this);
}

TosField::TosField (uint8_t tos) :
  m_tos (tos)
{
  NS_LOG_FUNCTION (this << (uint32_t) tos);
}

TosField::~TosField ()
{
  NS_LOG_FUNCTION (this);
}

bool
TosField::Match (Ptr<Packet> p)
{
  NS_LOG_FUNCTION (this << p);
  
  // Create a copy of the packet
  Ptr<Packet> copy = p->Copy ();
  
  // Try to remove the IPv4 header
  Ipv4Header ipHeader;
  if (copy->PeekHeader (ipHeader))
    {
      NS_LOG_LOGIC ("Found IPv4 header, ToS = " << (uint32_t) ipHeader.GetTos ());
      return ipHeader.GetTos () == m_tos;
    }
  
  NS_LOG_LOGIC ("No IPv4 header found");
  return false;
}

void
TosField::SetTos (uint8_t tos)
{
  NS_LOG_FUNCTION (this << (uint32_t) tos);
  m_tos = tos;
}

uint8_t
TosField::GetTos (void) const
{
  NS_LOG_FUNCTION (this);
  return m_tos;
}

} // namespace ns3