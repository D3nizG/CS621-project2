// dest-ip-address.cc
#include "dest-ip-address.h"
#include "ns3/log.h"
#include "ns3/ipv4-header.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("DestIpAddress");
NS_OBJECT_ENSURE_REGISTERED (DestIpAddress);

TypeId
DestIpAddress::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::DestIpAddress")
    .SetParent<FilterElement> ()
    .SetGroupName ("Network")
    .AddConstructor<DestIpAddress> ()
  ;
  return tid;
}

DestIpAddress::DestIpAddress () :
  m_address (Ipv4Address::GetAny ())
{
  NS_LOG_FUNCTION (this);
}

DestIpAddress::DestIpAddress (Ipv4Address addr) :
  m_address (addr)
{
  NS_LOG_FUNCTION (this << addr);
}

DestIpAddress::~DestIpAddress ()
{
  NS_LOG_FUNCTION (this);
}

bool
DestIpAddress::Match (Ptr<Packet> p)
{
  NS_LOG_FUNCTION (this << p);
  
  // Create a copy of the packet
  Ptr<Packet> copy = p->Copy ();
  
  // Try to remove the IPv4 header
  Ipv4Header ipHeader;
  if (copy->PeekHeader (ipHeader))
    {
      NS_LOG_LOGIC ("Found IPv4 header, destination IP = " << ipHeader.GetDestination ());
      return ipHeader.GetDestination () == m_address;
    }
  
  NS_LOG_LOGIC ("No IPv4 header found");
  return false;
}

void
DestIpAddress::SetAddress (Ipv4Address addr)
{
  NS_LOG_FUNCTION (this << addr);
  m_address = addr;
}

Ipv4Address
DestIpAddress::GetAddress (void) const
{
  NS_LOG_FUNCTION (this);
  return m_address;
}
} // namespace ns3