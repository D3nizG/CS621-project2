// source-port.h
/**
 * \brief Filter element for source port
 */
class SourcePort : public FilterElement
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
  SourcePort ();
  
  /**
   * \brief Constructor with port number
   * \param port The source port to match
   */
  SourcePort (uint16_t port);
  
  /**
   * \brief Destructor
   */
  virtual ~SourcePort ();
  
  /**
   * \brief Check if a packet matches this filter element
   * \param p The packet to check
   * \return True if the packet matches this filter element
   */
  virtual bool Match (Ptr<Packet> p);
  
  /**
   * \brief Set the source port to match
   * \param port The source port
   */
  void SetPort (uint16_t port);
  
  /**
   * \brief Get the source port to match
   * \return The source port
   */
  uint16_t GetPort (void) const;

private:
  uint16_t m_port; //!< The source port to match
};