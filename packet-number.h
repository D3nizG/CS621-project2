// packet-number.h
/**
 * \brief Filter element for packet number
 */
class PacketNumber : public FilterElement
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
  PacketNumber ();
  
  /**
   * \brief Constructor with packet number
   * \param number The packet number to match
   */
  PacketNumber (uint32_t number);
  
  /**
   * \brief Destructor
   */
  virtual ~PacketNumber ();
  
  /**
   * \brief Check if a packet matches this filter element
   * \param p The packet to check
   * \return True if the packet matches this filter element
   */
  virtual bool Match (Ptr<Packet> p);
  
  /**
   * \brief Set the packet number to match
   * \param number The packet number
   */
  void SetNumber (uint32_t number);
  
  /**
   * \brief Get the packet number to match
   * \return The packet number
   */
  uint32_t GetNumber (void) const;

private:
  uint32_t m_number; //!< The packet number to match
  static uint32_t s_packetCount; //!< Static packet counter
};