// packet-number.cc
#include "packet-number.h"
#include "ns3/log.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("PacketNumber");
NS_OBJECT_ENSURE_REGISTERED (PacketNumber);

// Initialize static packet counter
uint32_t PacketNumber::s_packetCount = 0;

TypeId
PacketNumber::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::PacketNumber")
    .SetParent<FilterElement> ()
    .SetGroupName ("Network")
    .AddConstructor<PacketNumber> ()
  ;
  return tid;
}

PacketNumber::PacketNumber () :
  m_number (0)
{
  NS_LOG_FUNCTION (this);
}

PacketNumber::PacketNumber (uint32_t number) :
  m_number (number)
{
  NS_LOG_FUNCTION (this << number);
}

PacketNumber::~PacketNumber ()
{
  NS_LOG_FUNCTION (this);
}

bool
PacketNumber::Match (Ptr<Packet> p)
{
  NS_LOG_FUNCTION (this << p);
  
  // Increment the static packet counter for each packet checked
  s_packetCount++;
  
  NS_LOG_LOGIC ("Packet count = " << s_packetCount << ", matching against " << m_number);
  
  // Check if the current packet count matches the specified number
  return (s_packetCount % m_number == 0);
}

void
PacketNumber::SetNumber (uint32_t number)
{
  NS_LOG_FUNCTION (this << number);
  m_number = number;
}

uint32_t
PacketNumber::GetNumber (void) const
{
  NS_LOG_FUNCTION (this);
  return m_number;
}
} // namespace ns3