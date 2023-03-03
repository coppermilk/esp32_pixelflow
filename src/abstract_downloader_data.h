
class AbstractDownloaderData{
  public:
  virtual ~AbstractDownloaderData() = default;
  virtual unsigned * downloadData(unsigned array_size);
};
