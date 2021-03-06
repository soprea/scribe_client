/**
 * Autogenerated by Thrift Compiler (1.0.0-dev)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef scribe_H
#define scribe_H

#include <thrift/TDispatchProcessor.h>
#include "scribe_types.h"
#include "FacebookService.h"

namespace scribe { namespace thrift {

class scribeIf : virtual public  ::facebook::fb303::FacebookServiceIf {
 public:
  virtual ~scribeIf() {}
  virtual ResultCode Log(const std::vector<LogEntry> & messages) = 0;
};

class scribeIfFactory : virtual public  ::facebook::fb303::FacebookServiceIfFactory {
 public:
  typedef scribeIf Handler;

  virtual ~scribeIfFactory() {}

  virtual scribeIf* getHandler(const ::apache::thrift::TConnectionInfo& connInfo) = 0;
  virtual void releaseHandler( ::facebook::fb303::FacebookServiceIf* /* handler */) = 0;
};

class scribeIfSingletonFactory : virtual public scribeIfFactory {
 public:
  scribeIfSingletonFactory(const boost::shared_ptr<scribeIf>& iface) : iface_(iface) {}
  virtual ~scribeIfSingletonFactory() {}

  virtual scribeIf* getHandler(const ::apache::thrift::TConnectionInfo&) {
    return iface_.get();
  }
  virtual void releaseHandler( ::facebook::fb303::FacebookServiceIf* /* handler */) {}

 protected:
  boost::shared_ptr<scribeIf> iface_;
};

class scribeNull : virtual public scribeIf , virtual public  ::facebook::fb303::FacebookServiceNull {
 public:
  virtual ~scribeNull() {}
  ResultCode Log(const std::vector<LogEntry> & /* messages */) {
    ResultCode _return = (ResultCode)0;
    return _return;
  }
};

typedef struct _scribe_Log_args__isset {
  _scribe_Log_args__isset() : messages(false) {}
  bool messages :1;
} _scribe_Log_args__isset;

class scribe_Log_args {
 public:

  static const char* ascii_fingerprint; // = "006EFB9C0A4E436459CDFDF617590BB4";
  static const uint8_t binary_fingerprint[16]; // = {0x00,0x6E,0xFB,0x9C,0x0A,0x4E,0x43,0x64,0x59,0xCD,0xFD,0xF6,0x17,0x59,0x0B,0xB4};

  scribe_Log_args(const scribe_Log_args&);
  scribe_Log_args& operator=(const scribe_Log_args&);
  scribe_Log_args() {
  }

  virtual ~scribe_Log_args() throw();
  std::vector<LogEntry>  messages;

  _scribe_Log_args__isset __isset;

  void __set_messages(const std::vector<LogEntry> & val);

  bool operator == (const scribe_Log_args & rhs) const
  {
    if (!(messages == rhs.messages))
      return false;
    return true;
  }
  bool operator != (const scribe_Log_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const scribe_Log_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class scribe_Log_pargs {
 public:

  static const char* ascii_fingerprint; // = "006EFB9C0A4E436459CDFDF617590BB4";
  static const uint8_t binary_fingerprint[16]; // = {0x00,0x6E,0xFB,0x9C,0x0A,0x4E,0x43,0x64,0x59,0xCD,0xFD,0xF6,0x17,0x59,0x0B,0xB4};


  virtual ~scribe_Log_pargs() throw();
  const std::vector<LogEntry> * messages;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _scribe_Log_result__isset {
  _scribe_Log_result__isset() : success(false) {}
  bool success :1;
} _scribe_Log_result__isset;

class scribe_Log_result {
 public:

  static const char* ascii_fingerprint; // = "F1BC2174724B9D2E335CD95F6D6F9367";
  static const uint8_t binary_fingerprint[16]; // = {0xF1,0xBC,0x21,0x74,0x72,0x4B,0x9D,0x2E,0x33,0x5C,0xD9,0x5F,0x6D,0x6F,0x93,0x67};

  scribe_Log_result(const scribe_Log_result&);
  scribe_Log_result& operator=(const scribe_Log_result&);
  scribe_Log_result() : success((ResultCode)0) {
  }

  virtual ~scribe_Log_result() throw();
  ResultCode success;

  _scribe_Log_result__isset __isset;

  void __set_success(const ResultCode val);

  bool operator == (const scribe_Log_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const scribe_Log_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const scribe_Log_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _scribe_Log_presult__isset {
  _scribe_Log_presult__isset() : success(false) {}
  bool success :1;
} _scribe_Log_presult__isset;

class scribe_Log_presult {
 public:

  static const char* ascii_fingerprint; // = "F1BC2174724B9D2E335CD95F6D6F9367";
  static const uint8_t binary_fingerprint[16]; // = {0xF1,0xBC,0x21,0x74,0x72,0x4B,0x9D,0x2E,0x33,0x5C,0xD9,0x5F,0x6D,0x6F,0x93,0x67};


  virtual ~scribe_Log_presult() throw();
  ResultCode* success;

  _scribe_Log_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

class scribeClient : virtual public scribeIf, public  ::facebook::fb303::FacebookServiceClient {
 public:
  scribeClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) :
     ::facebook::fb303::FacebookServiceClient(prot, prot) {}
  scribeClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) :     ::facebook::fb303::FacebookServiceClient(iprot, oprot) {}
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  ResultCode Log(const std::vector<LogEntry> & messages);
  void send_Log(const std::vector<LogEntry> & messages);
  ResultCode recv_Log();
};

class scribeProcessor : public  ::facebook::fb303::FacebookServiceProcessor {
 protected:
  boost::shared_ptr<scribeIf> iface_;
  virtual bool dispatchCall(::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, const std::string& fname, int32_t seqid, void* callContext);
 private:
  typedef  void (scribeProcessor::*ProcessFunction)(int32_t, ::apache::thrift::protocol::TProtocol*, ::apache::thrift::protocol::TProtocol*, void*);
  typedef std::map<std::string, ProcessFunction> ProcessMap;
  ProcessMap processMap_;
  void process_Log(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
 public:
  scribeProcessor(boost::shared_ptr<scribeIf> iface) :
     ::facebook::fb303::FacebookServiceProcessor(iface),
    iface_(iface) {
    processMap_["Log"] = &scribeProcessor::process_Log;
  }

  virtual ~scribeProcessor() {}
};

class scribeProcessorFactory : public ::apache::thrift::TProcessorFactory {
 public:
  scribeProcessorFactory(const ::boost::shared_ptr< scribeIfFactory >& handlerFactory) :
      handlerFactory_(handlerFactory) {}

  ::boost::shared_ptr< ::apache::thrift::TProcessor > getProcessor(const ::apache::thrift::TConnectionInfo& connInfo);

 protected:
  ::boost::shared_ptr< scribeIfFactory > handlerFactory_;
};

class scribeMultiface : virtual public scribeIf, public  ::facebook::fb303::FacebookServiceMultiface {
 public:
  scribeMultiface(std::vector<boost::shared_ptr<scribeIf> >& ifaces) : ifaces_(ifaces) {
    std::vector<boost::shared_ptr<scribeIf> >::iterator iter;
    for (iter = ifaces.begin(); iter != ifaces.end(); ++iter) {
       ::facebook::fb303::FacebookServiceMultiface::add(*iter);
    }
  }
  virtual ~scribeMultiface() {}
 protected:
  std::vector<boost::shared_ptr<scribeIf> > ifaces_;
  scribeMultiface() {}
  void add(boost::shared_ptr<scribeIf> iface) {
     ::facebook::fb303::FacebookServiceMultiface::add(iface);
    ifaces_.push_back(iface);
  }
 public:
  ResultCode Log(const std::vector<LogEntry> & messages) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->Log(messages);
    }
    return ifaces_[i]->Log(messages);
  }

};

}} // namespace

#endif
