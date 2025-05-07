// filter-element.h
#ifndef FILTER_ELEMENT_H
#define FILTER_ELEMENT_H

#include "ns3/packet.h"
#include "ns3/object.h"

namespace ns3 {

/**
 * \brief Base class for filter elements
 *
 * This class represents a basic filter element in DiffServ architecture.
 * It is a base class for all specific filter element types.
 */
class FilterElement : public Object
{
public:
  /**
   * \brief Get the type ID.
   * \return the object TypeId
   */
  static TypeId GetTypeId (void);
  
  /**
   * \brief Constructor
   */
  FilterElement ();
  
  /**
   * \brief Destructor
   */
  virtual ~FilterElement ();
  
  /**
   * \brief Check if a packet matches this filter element
   * \param p The packet to check
   * \return True if the packet matches this filter element
   */
  virtual bool Match (Ptr<Packet> p) = 0;

protected:
  /**
   * \brief Dispose of the object
   */
  virtual void DoDispose (void);
};

} // namespace ns3

#endif /* FILTER_ELEMENT_H */

