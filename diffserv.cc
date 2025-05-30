// diffserv.cc
#include "diffserv.h"
#include "traffic-class.h"
#include "ns3/log.h"
#include "ns3/enum.h"
#include "ns3/uinteger.h"
#include "ns3/pointer.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("DiffServ");
NS_OBJECT_ENSURE_REGISTERED (DiffServ);

TypeId
DiffServ::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::DiffServ")
    .SetParent<Queue<Packet> > ()
    .SetGroupName ("Network")
    .AddConstructor<DiffServ> ()
    .AddAttribute ("MaxSize",
                   "The maximum number of packets accepted by this DiffServ queue.",
                   QueueSizeValue (QueueSize ("100p")),
                   MakeQueueSizeAccessor (&QueueBase::SetMaxSize,
                                          &QueueBase::GetMaxSize),
                   MakeQueueSizeChecker ())
  ;
  return tid;
}

DiffServ::DiffServ () :
  Queue<Packet> (),
  m_classes ()
{
  NS_LOG_FUNCTION (this);
}

DiffServ::~DiffServ ()
{
  NS_LOG_FUNCTION (this);
}

void
DiffServ::DoDispose (void)
{
  NS_LOG_FUNCTION (this);
  m_classes.clear ();
  Queue<Packet>::DoDispose ();
}

bool
DiffServ::DoEnqueue (Ptr<Packet> p)
{
  NS_LOG_FUNCTION (this << p);
  
  if (GetNPackets () >= GetMaxSize().GetValue ())
    {
      NS_LOG_LOGIC ("Queue full -- dropping packet");
      return false;
    }
  
  uint32_t classIndex = Classify (p);
  if (classIndex >= m_classes.size ())
    {
      NS_LOG_LOGIC ("No matching traffic class, using default (0)");
      classIndex = 0;
    }
  
  if (m_classes[classIndex]->Enqueue (p))
    {
      NS_LOG_LOGIC ("Packet enqueued in traffic class " << classIndex);
      return true;
    }
  return false;
}

Ptr<Packet>
DiffServ::DoDequeue (void)
{
  NS_LOG_FUNCTION (this);
  
  if (IsEmpty ())
    {
      NS_LOG_LOGIC ("Queue empty");
      return 0;
    }
  
  Ptr<Packet> p = Schedule ();
  if (p)
    {
      NS_LOG_LOGIC ("Packet dequeued");
    }
  return p;
}

Ptr<Packet>
DiffServ::DoPeek (void) const
{
  NS_LOG_FUNCTION (this);
  
  if (IsEmpty ())
    {
      NS_LOG_LOGIC ("Queue empty");
      return 0;
    }
  
  // This is not entirely correct since it doesn't respect the scheduling discipline,
  // but it's a reasonable approximation for peeking
  for (uint32_t i = 0; i < m_classes.size (); i++)
    {
      if (!m_classes[i]->IsEmpty ())
        {
          NS_LOG_LOGIC ("Peeking from traffic class " << i);
          return m_classes[i]->Peek ();
        }
    }
  
  NS_LOG_LOGIC ("No packet found in peek");
  return 0;
}

bool
DiffServ::IsEmpty (void) const
{
  NS_LOG_FUNCTION (this);
  
  for (uint32_t i = 0; i < m_classes.size (); i++)
    {
      if (!m_classes[i]->IsEmpty ())
        {
          NS_LOG_LOGIC ("Traffic class " << i << " is not empty");
          return false;
        }
    }
  
  NS_LOG_LOGIC ("All traffic classes are empty");
  return true;
}

Ptr<Packet>
DiffServ::Schedule (void)
{
  NS_LOG_FUNCTION (this);
  
  // Default scheduler - round robin
  // Subclasses should override this method
  for (uint32_t i = 0; i < m_classes.size (); i++)
    {
      if (!m_classes[i]->IsEmpty ())
        {
          NS_LOG_LOGIC ("Scheduling from traffic class " << i);
          return m_classes[i]->Dequeue ();
        }
    }
  
  NS_LOG_LOGIC ("No packet found in scheduling");
  return 0;
}

uint32_t
DiffServ::Classify (Ptr<Packet> p)
{
  NS_LOG_FUNCTION (this << p);
  
  // Default classifier - check all traffic classes
  for (uint32_t i = 0; i < m_classes.size (); i++)
    {
      if (m_classes[i]->Match (p))
        {
          NS_LOG_LOGIC ("Packet matches traffic class " << i);
          return i;
        }
    }
  
  // If no match, return 0 (best effort class)
  NS_LOG_LOGIC ("No matching traffic class, using default (0)");
  return 0;
}

void
DiffServ::AddTrafficClass (Ptr<TrafficClass> tClass)
{
  NS_LOG_FUNCTION (this << tClass);
  m_classes.push_back (tClass);
}

Ptr<TrafficClass>
DiffServ::GetTrafficClass (uint32_t index) const
{
  NS_LOG_FUNCTION (this << index);
  if (index < m_classes.size ())
    {
      return m_classes[index];
    }
  return 0;
}

uint32_t
DiffServ::GetNTrafficClasses (void) const
{
  NS_LOG_FUNCTION (this);
  return m_classes.size ();
}

} // namespace ns3