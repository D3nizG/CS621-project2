// source-port.cc
#include "source-port.h"
#include "ns3/log.h"
#include "ns3/ipv4-header.h"
#include "ns3/tcp-header.h"
#include "ns3/udp-header.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("SourcePort");
NS_OBJECT_ENSURE_REGISTERED (SourcePort);

TypeId
SourcePort::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::SourcePort")
    .SetParent<FilterElement> ()
    .SetGroupName ("Network")
    .AddConstructor<SourcePort> ()
  ;
  return tid;
}

SourcePort::SourcePort () :
  m_port (0)
{
  NS_LOG_FUNCTION (this);
}

SourcePort::SourcePort (uint16_t port) :
  m_port (port)
{
  NS_LOG_FUNCTION (this << port);
}

SourcePort::~SourcePort ()
{
  NS_LOG_FUNCTION (this);
}

bool
SourcePort::Match (Ptr<Packet> p)
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
              NS_LOG_LOGIC ("Found TCP header, source port = " << tcpHeader.GetSourcePort ());
              return tcpHeader.GetSourcePort () == m_port;
            }
        }
      else if (protocol == 17) // UDP
        {
          UdpHeader udpHeader;
          if (copy->PeekHeader (udpHeader))
            {
              NS_LOG_LOGIC ("Found UDP header, source port = " << udpHeader.GetSourcePort ());
              return udpHeader.GetSourcePort () == m_port;
            }
        }
    }
  
  NS_LOG_LOGIC ("No matching transport header found");
  return false;
}

void
SourcePort::SetPort (uint16_t port)
{
  NS_LOG_FUNCTION (this << port);
  m_port = port;
}

uint16_t
SourcePort::GetPort (void) const
{
  NS_LOG_FUNCTION (this);
  return m_port;
}

} // namespace ns3