// protocol-number.cc
#include "protocol-number.h"
#include "ns3/log.h"
#include "ns3/ipv4-header.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("ProtocolNumber");
NS_OBJECT_ENSURE_REGISTERED (ProtocolNumber);

TypeId
ProtocolNumber::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::ProtocolNumber")
    .SetParent<FilterElement> ()
    .SetGroupName ("Network")
    .AddConstructor<ProtocolNumber> ()
  ;
  return tid;
}

ProtocolNumber::ProtocolNumber () :
  m_protocol (0)
{
  NS_LOG_FUNCTION (this);
}

ProtocolNumber::ProtocolNumber (uint8_t protocol) :
  m_protocol (protocol)
{
  NS_LOG_FUNCTION (this << (uint32_t) protocol);
}

ProtocolNumber::~ProtocolNumber ()
{
  NS_LOG_FUNCTION (this);
}

bool
ProtocolNumber::Match (Ptr<Packet> p)
{
  NS_LOG_FUNCTION (this << p);
  
  // Create a copy of the packet
  Ptr<Packet> copy = p->Copy ();
  
  // Try to remove the IPv4 header
  Ipv4Header ipHeader;
  if (copy->PeekHeader (ipHeader))
    {
      NS_LOG_LOGIC ("Found IPv4 header, protocol = " << (uint32_t) ipHeader.GetProtocol ());
      return ipHeader.GetProtocol () == m_protocol;
    }
  
  NS_LOG_LOGIC ("No IPv4 header found");
  return false;
}

void
ProtocolNumber::SetProtocol (uint8_t protocol)
{
  NS_LOG_FUNCTION (this << (uint32_t) protocol);
  m_protocol = protocol;
}

uint8_t
ProtocolNumber::GetProtocol (void) const
{
  NS_LOG_FUNCTION (this);
  return m_protocol;
}
} // namespace ns3