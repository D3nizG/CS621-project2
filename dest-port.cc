// dest-port.cc
#include "dest-port.h"
#include "ns3/log.h"
#include "ns3/ipv4-header.h"
#include "ns3/tcp-header.h"
#include "ns3/udp-header.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("DestPort");
NS_OBJECT_ENSURE_REGISTERED (DestPort);

TypeId
DestPort::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::DestPort")
    .SetParent<FilterElement> ()
    .SetGroupName ("Network")
    .AddConstructor<DestPort> ()
  ;
  return tid;
}

DestPort::DestPort () :
  m_port (0)
{
  NS_LOG_FUNCTION (this);
}

DestPort::DestPort (uint16_t port) :
  m_port (port)
{
  NS_LOG_FUNCTION (this << port);
}

DestPort::~DestPort ()
{
  NS_LOG_FUNCTION (this);
}

bool
DestPort::Match (Ptr<Packet> p)
{
  NS_LOG_FUNCTION (this << p);
  
  // Create a copy of the packet
  Ptr<Packet> copy = p->Copy ();
  
  // Try to remove the IPv4 header
  Ipv4Header ipHeader;
  if (copy->RemoveHeader (ipHeader))
    {
      // Check the protocol
      uint8_t protocol = ipHeader.GetProtocol ();
      
      if (protocol == 6) // TCP
        {
          TcpHeader tcpHeader;
          if (copy->PeekHeader (tcpHeader))
            {
              NS_LOG_LOGIC ("Found TCP header, destination port = " << tcpHeader.GetDestinationPort ());
              return tcpHeader.GetDestinationPort () == m_port;
            }
        }
      else if (protocol == 17) // UDP
        {
          UdpHeader udpHeader;
          if (copy->PeekHeader (udpHeader))
            {
              NS_LOG_LOGIC ("Found UDP header, destination port = " << udpHeader.GetDestinationPort ());
              return udpHeader.GetDestinationPort () == m_port;
            }
        }
    }
  
  NS_LOG_LOGIC ("No matching transport header found");
  return false;
}

void
DestPort::SetPort (uint16_t port)
{
  NS_LOG_FUNCTION (this << port);
  m_port = port;
}

uint16_t
DestPort::GetPort (void) const
{
  NS_LOG_FUNCTION (this);
  return m_port;
}

} // namespace ns3