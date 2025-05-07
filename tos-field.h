// tos-field.h
/**
 * \brief Filter element for ToS (Type of Service) field
 */
class TosField : public FilterElement
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
  TosField ();
  
  /**
   * \brief Constructor with ToS value
   * \param tos The ToS value to match
   */
  TosField (uint8_t tos);
  
  /**
   * \brief Destructor
   */
  virtual ~TosField ();
  
  /**
   * \brief Check if a packet matches this filter element
   * \param p The packet to check
   * \return True if the packet matches this filter element
   */
  virtual bool Match (Ptr<Packet> p);
  
  /**
   * \brief Set the ToS value to match
   * \param tos The ToS value
   */
  void SetTos (uint8_t tos);
  
  /**
   * \brief Get the ToS value to match
   * \return The ToS value
   */
  uint8_t GetTos (void) const;

private:
  uint8_t m_tos; //!< The ToS value to match
};
