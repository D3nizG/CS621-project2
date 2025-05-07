// protocol-number.h
/**
 * \brief Filter element for protocol number
 */
class ProtocolNumber : public FilterElement
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
  ProtocolNumber ();
  
  /**
   * \brief Constructor with protocol number
   * \param protocol The protocol number to match
   */
  ProtocolNumber (uint8_t protocol);
  
  /**
   * \brief Destructor
   */
  virtual ~ProtocolNumber ();
  
  /**
   * \brief Check if a packet matches this filter element
   * \param p The packet to check
   * \return True if the packet matches this filter element
   */
  virtual bool Match (Ptr<Packet> p);
  
  /**
   * \brief Set the protocol number to match
   * \param protocol The protocol number
   */
  void SetProtocol (uint8_t protocol);
  
  /**
   * \brief Get the protocol number to match
   * \return The protocol number
   */
  uint8_t GetProtocol (void) const;

private:
  uint8_t m_protocol; //!< The protocol number to match
};