// dest-port.h
/**
 * \brief Filter element for destination port
 */
class DestPort : public FilterElement
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
  DestPort ();
  
  /**
   * \brief Constructor with port number
   * \param port The destination port to match
   */
  DestPort (uint16_t port);
  
  /**
   * \brief Destructor
   */
  virtual ~DestPort ();
  
  /**
   * \brief Check if a packet matches this filter element
   * \param p The packet to check
   * \return True if the packet matches this filter element
   */
  virtual bool Match (Ptr<Packet> p);
  
  /**
   * \brief Set the destination port to match
   * \param port The destination port
   */
  void SetPort (uint16_t port);
  
  /**
   * \brief Get the destination port to match
   * \return The destination port
   */
  uint16_t GetPort (void) const;

private:
  uint16_t m_port; //!< The destination port to match
};