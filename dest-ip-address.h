// dest-ip-address.h
/**
 * \brief Filter element for destination IP address
 */
class DestIpAddress : public FilterElement
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
  DestIpAddress ();
  
  /**
   * \brief Constructor with IP address
   * \param addr The destination IP address to match
   */
  DestIpAddress (Ipv4Address addr);
  
  /**
   * \brief Destructor
   */
  virtual ~DestIpAddress ();
  
  /**
   * \brief Check if a packet matches this filter element
   * \param p The packet to check
   * \return True if the packet matches this filter element
   */
  virtual bool Match (Ptr<Packet> p);
  
  /**
   * \brief Set the destination IP address to match
   * \param addr The destination IP address
   */
  void SetAddress (Ipv4Address addr);
  
  /**
   * \brief Get the destination IP address to match
   * \return The destination IP address
   */
  Ipv4Address GetAddress (void) const;

private:
  Ipv4Address m_address; //!< The destination IP address to match
};