// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: daily_auction.proto

#ifndef PROTOBUF_daily_5fauction_2eproto__INCLUDED
#define PROTOBUF_daily_5fauction_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2005000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
#include "goods.pb.h"
// @@protoc_insertion_point(includes)

namespace app {
namespace message {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_daily_5fauction_2eproto();
void protobuf_AssignDesc_daily_5fauction_2eproto();
void protobuf_ShutdownFile_daily_5fauction_2eproto();

class DailyAuctionConfigProto;
class SingleDailyAuctionConfig;
class GlobalAuctionData;

// ===================================================================

class DailyAuctionConfigProto : public ::google::protobuf::Message {
 public:
  DailyAuctionConfigProto();
  virtual ~DailyAuctionConfigProto();

  DailyAuctionConfigProto(const DailyAuctionConfigProto& from);

  inline DailyAuctionConfigProto& operator=(const DailyAuctionConfigProto& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const DailyAuctionConfigProto& default_instance();

  void Swap(DailyAuctionConfigProto* other);

  // implements Message ----------------------------------------------

  DailyAuctionConfigProto* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const DailyAuctionConfigProto& from);
  void MergeFrom(const DailyAuctionConfigProto& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // repeated .app.message.SingleDailyAuctionConfig config_list = 1;
  inline int config_list_size() const;
  inline void clear_config_list();
  static const int kConfigListFieldNumber = 1;
  inline const ::app::message::SingleDailyAuctionConfig& config_list(int index) const;
  inline ::app::message::SingleDailyAuctionConfig* mutable_config_list(int index);
  inline ::app::message::SingleDailyAuctionConfig* add_config_list();
  inline const ::google::protobuf::RepeatedPtrField< ::app::message::SingleDailyAuctionConfig >&
      config_list() const;
  inline ::google::protobuf::RepeatedPtrField< ::app::message::SingleDailyAuctionConfig >*
      mutable_config_list();

  // optional int64 start_time = 2;
  inline bool has_start_time() const;
  inline void clear_start_time();
  static const int kStartTimeFieldNumber = 2;
  inline ::google::protobuf::int64 start_time() const;
  inline void set_start_time(::google::protobuf::int64 value);

  // optional int64 end_time = 3;
  inline bool has_end_time() const;
  inline void clear_end_time();
  static const int kEndTimeFieldNumber = 3;
  inline ::google::protobuf::int64 end_time() const;
  inline void set_end_time(::google::protobuf::int64 value);

  // optional bytes auction_goods = 4;
  inline bool has_auction_goods() const;
  inline void clear_auction_goods();
  static const int kAuctionGoodsFieldNumber = 4;
  inline const ::std::string& auction_goods() const;
  inline void set_auction_goods(const ::std::string& value);
  inline void set_auction_goods(const char* value);
  inline void set_auction_goods(const void* value, size_t size);
  inline ::std::string* mutable_auction_goods();
  inline ::std::string* release_auction_goods();
  inline void set_allocated_auction_goods(::std::string* auction_goods);

  // optional int32 yuanbao_price = 5;
  inline bool has_yuanbao_price() const;
  inline void clear_yuanbao_price();
  static const int kYuanbaoPriceFieldNumber = 5;
  inline ::google::protobuf::int32 yuanbao_price() const;
  inline void set_yuanbao_price(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:app.message.DailyAuctionConfigProto)
 private:
  inline void set_has_start_time();
  inline void clear_has_start_time();
  inline void set_has_end_time();
  inline void clear_has_end_time();
  inline void set_has_auction_goods();
  inline void clear_has_auction_goods();
  inline void set_has_yuanbao_price();
  inline void clear_has_yuanbao_price();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::RepeatedPtrField< ::app::message::SingleDailyAuctionConfig > config_list_;
  ::google::protobuf::int64 start_time_;
  ::google::protobuf::int64 end_time_;
  ::std::string* auction_goods_;
  ::google::protobuf::int32 yuanbao_price_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(5 + 31) / 32];

  friend void  protobuf_AddDesc_daily_5fauction_2eproto();
  friend void protobuf_AssignDesc_daily_5fauction_2eproto();
  friend void protobuf_ShutdownFile_daily_5fauction_2eproto();

  void InitAsDefaultInstance();
  static DailyAuctionConfigProto* default_instance_;
};
// -------------------------------------------------------------------

class SingleDailyAuctionConfig : public ::google::protobuf::Message {
 public:
  SingleDailyAuctionConfig();
  virtual ~SingleDailyAuctionConfig();

  SingleDailyAuctionConfig(const SingleDailyAuctionConfig& from);

  inline SingleDailyAuctionConfig& operator=(const SingleDailyAuctionConfig& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const SingleDailyAuctionConfig& default_instance();

  void Swap(SingleDailyAuctionConfig* other);

  // implements Message ----------------------------------------------

  SingleDailyAuctionConfig* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const SingleDailyAuctionConfig& from);
  void MergeFrom(const SingleDailyAuctionConfig& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional int32 id = 1;
  inline bool has_id() const;
  inline void clear_id();
  static const int kIdFieldNumber = 1;
  inline ::google::protobuf::int32 id() const;
  inline void set_id(::google::protobuf::int32 value);

  // optional bytes desc = 2;
  inline bool has_desc() const;
  inline void clear_desc();
  static const int kDescFieldNumber = 2;
  inline const ::std::string& desc() const;
  inline void set_desc(const ::std::string& value);
  inline void set_desc(const char* value);
  inline void set_desc(const void* value, size_t size);
  inline ::std::string* mutable_desc();
  inline ::std::string* release_desc();
  inline void set_allocated_desc(::std::string* desc);

  // optional int32 minYuanbao = 3 [deprecated = true];
  inline bool has_minyuanbao() const PROTOBUF_DEPRECATED;
  inline void clear_minyuanbao() PROTOBUF_DEPRECATED;
  static const int kMinYuanbaoFieldNumber = 3;
  inline ::google::protobuf::int32 minyuanbao() const PROTOBUF_DEPRECATED;
  inline void set_minyuanbao(::google::protobuf::int32 value) PROTOBUF_DEPRECATED;

  // optional .app.message.GoodsWrapperProto prize = 4;
  inline bool has_prize() const;
  inline void clear_prize();
  static const int kPrizeFieldNumber = 4;
  inline const ::app::message::GoodsWrapperProto& prize() const;
  inline ::app::message::GoodsWrapperProto* mutable_prize();
  inline ::app::message::GoodsWrapperProto* release_prize();
  inline void set_allocated_prize(::app::message::GoodsWrapperProto* prize);

  // optional int32 min_auction_goods = 5;
  inline bool has_min_auction_goods() const;
  inline void clear_min_auction_goods();
  static const int kMinAuctionGoodsFieldNumber = 5;
  inline ::google::protobuf::int32 min_auction_goods() const;
  inline void set_min_auction_goods(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:app.message.SingleDailyAuctionConfig)
 private:
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_desc();
  inline void clear_has_desc();
  inline void set_has_minyuanbao();
  inline void clear_has_minyuanbao();
  inline void set_has_prize();
  inline void clear_has_prize();
  inline void set_has_min_auction_goods();
  inline void clear_has_min_auction_goods();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::std::string* desc_;
  ::google::protobuf::int32 id_;
  ::google::protobuf::int32 minyuanbao_;
  ::app::message::GoodsWrapperProto* prize_;
  ::google::protobuf::int32 min_auction_goods_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(5 + 31) / 32];

  friend void  protobuf_AddDesc_daily_5fauction_2eproto();
  friend void protobuf_AssignDesc_daily_5fauction_2eproto();
  friend void protobuf_ShutdownFile_daily_5fauction_2eproto();

  void InitAsDefaultInstance();
  static SingleDailyAuctionConfig* default_instance_;
};
// -------------------------------------------------------------------

class GlobalAuctionData : public ::google::protobuf::Message {
 public:
  GlobalAuctionData();
  virtual ~GlobalAuctionData();

  GlobalAuctionData(const GlobalAuctionData& from);

  inline GlobalAuctionData& operator=(const GlobalAuctionData& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const GlobalAuctionData& default_instance();

  void Swap(GlobalAuctionData* other);

  // implements Message ----------------------------------------------

  GlobalAuctionData* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const GlobalAuctionData& from);
  void MergeFrom(const GlobalAuctionData& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // repeated int32 id = 1;
  inline int id_size() const;
  inline void clear_id();
  static const int kIdFieldNumber = 1;
  inline ::google::protobuf::int32 id(int index) const;
  inline void set_id(int index, ::google::protobuf::int32 value);
  inline void add_id(::google::protobuf::int32 value);
  inline const ::google::protobuf::RepeatedField< ::google::protobuf::int32 >&
      id() const;
  inline ::google::protobuf::RepeatedField< ::google::protobuf::int32 >*
      mutable_id();

  // repeated int64 herod_id = 2;
  inline int herod_id_size() const;
  inline void clear_herod_id();
  static const int kHerodIdFieldNumber = 2;
  inline ::google::protobuf::int64 herod_id(int index) const;
  inline void set_herod_id(int index, ::google::protobuf::int64 value);
  inline void add_herod_id(::google::protobuf::int64 value);
  inline const ::google::protobuf::RepeatedField< ::google::protobuf::int64 >&
      herod_id() const;
  inline ::google::protobuf::RepeatedField< ::google::protobuf::int64 >*
      mutable_herod_id();

  // repeated bytes hero_name = 3;
  inline int hero_name_size() const;
  inline void clear_hero_name();
  static const int kHeroNameFieldNumber = 3;
  inline const ::std::string& hero_name(int index) const;
  inline ::std::string* mutable_hero_name(int index);
  inline void set_hero_name(int index, const ::std::string& value);
  inline void set_hero_name(int index, const char* value);
  inline void set_hero_name(int index, const void* value, size_t size);
  inline ::std::string* add_hero_name();
  inline void add_hero_name(const ::std::string& value);
  inline void add_hero_name(const char* value);
  inline void add_hero_name(const void* value, size_t size);
  inline const ::google::protobuf::RepeatedPtrField< ::std::string>& hero_name() const;
  inline ::google::protobuf::RepeatedPtrField< ::std::string>* mutable_hero_name();

  // repeated int32 current_max_yuanbao = 4 [deprecated = true];
  inline int current_max_yuanbao_size() const PROTOBUF_DEPRECATED;
  inline void clear_current_max_yuanbao() PROTOBUF_DEPRECATED;
  static const int kCurrentMaxYuanbaoFieldNumber = 4;
  inline ::google::protobuf::int32 current_max_yuanbao(int index) const PROTOBUF_DEPRECATED;
  inline void set_current_max_yuanbao(int index, ::google::protobuf::int32 value) PROTOBUF_DEPRECATED;
  inline void add_current_max_yuanbao(::google::protobuf::int32 value) PROTOBUF_DEPRECATED;
  inline const ::google::protobuf::RepeatedField< ::google::protobuf::int32 >&
      current_max_yuanbao() const PROTOBUF_DEPRECATED;
  inline ::google::protobuf::RepeatedField< ::google::protobuf::int32 >*
      mutable_current_max_yuanbao() PROTOBUF_DEPRECATED;

  // repeated int32 current_max_price = 5;
  inline int current_max_price_size() const;
  inline void clear_current_max_price();
  static const int kCurrentMaxPriceFieldNumber = 5;
  inline ::google::protobuf::int32 current_max_price(int index) const;
  inline void set_current_max_price(int index, ::google::protobuf::int32 value);
  inline void add_current_max_price(::google::protobuf::int32 value);
  inline const ::google::protobuf::RepeatedField< ::google::protobuf::int32 >&
      current_max_price() const;
  inline ::google::protobuf::RepeatedField< ::google::protobuf::int32 >*
      mutable_current_max_price();

  // @@protoc_insertion_point(class_scope:app.message.GlobalAuctionData)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::RepeatedField< ::google::protobuf::int32 > id_;
  ::google::protobuf::RepeatedField< ::google::protobuf::int64 > herod_id_;
  ::google::protobuf::RepeatedPtrField< ::std::string> hero_name_;
  ::google::protobuf::RepeatedField< ::google::protobuf::int32 > current_max_yuanbao_;
  ::google::protobuf::RepeatedField< ::google::protobuf::int32 > current_max_price_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(5 + 31) / 32];

  friend void  protobuf_AddDesc_daily_5fauction_2eproto();
  friend void protobuf_AssignDesc_daily_5fauction_2eproto();
  friend void protobuf_ShutdownFile_daily_5fauction_2eproto();

  void InitAsDefaultInstance();
  static GlobalAuctionData* default_instance_;
};
// ===================================================================


// ===================================================================

// DailyAuctionConfigProto

// repeated .app.message.SingleDailyAuctionConfig config_list = 1;
inline int DailyAuctionConfigProto::config_list_size() const {
  return config_list_.size();
}
inline void DailyAuctionConfigProto::clear_config_list() {
  config_list_.Clear();
}
inline const ::app::message::SingleDailyAuctionConfig& DailyAuctionConfigProto::config_list(int index) const {
  return config_list_.Get(index);
}
inline ::app::message::SingleDailyAuctionConfig* DailyAuctionConfigProto::mutable_config_list(int index) {
  return config_list_.Mutable(index);
}
inline ::app::message::SingleDailyAuctionConfig* DailyAuctionConfigProto::add_config_list() {
  return config_list_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::app::message::SingleDailyAuctionConfig >&
DailyAuctionConfigProto::config_list() const {
  return config_list_;
}
inline ::google::protobuf::RepeatedPtrField< ::app::message::SingleDailyAuctionConfig >*
DailyAuctionConfigProto::mutable_config_list() {
  return &config_list_;
}

// optional int64 start_time = 2;
inline bool DailyAuctionConfigProto::has_start_time() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void DailyAuctionConfigProto::set_has_start_time() {
  _has_bits_[0] |= 0x00000002u;
}
inline void DailyAuctionConfigProto::clear_has_start_time() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void DailyAuctionConfigProto::clear_start_time() {
  start_time_ = GOOGLE_LONGLONG(0);
  clear_has_start_time();
}
inline ::google::protobuf::int64 DailyAuctionConfigProto::start_time() const {
  return start_time_;
}
inline void DailyAuctionConfigProto::set_start_time(::google::protobuf::int64 value) {
  set_has_start_time();
  start_time_ = value;
}

// optional int64 end_time = 3;
inline bool DailyAuctionConfigProto::has_end_time() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void DailyAuctionConfigProto::set_has_end_time() {
  _has_bits_[0] |= 0x00000004u;
}
inline void DailyAuctionConfigProto::clear_has_end_time() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void DailyAuctionConfigProto::clear_end_time() {
  end_time_ = GOOGLE_LONGLONG(0);
  clear_has_end_time();
}
inline ::google::protobuf::int64 DailyAuctionConfigProto::end_time() const {
  return end_time_;
}
inline void DailyAuctionConfigProto::set_end_time(::google::protobuf::int64 value) {
  set_has_end_time();
  end_time_ = value;
}

// optional bytes auction_goods = 4;
inline bool DailyAuctionConfigProto::has_auction_goods() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void DailyAuctionConfigProto::set_has_auction_goods() {
  _has_bits_[0] |= 0x00000008u;
}
inline void DailyAuctionConfigProto::clear_has_auction_goods() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void DailyAuctionConfigProto::clear_auction_goods() {
  if (auction_goods_ != &::google::protobuf::internal::kEmptyString) {
    auction_goods_->clear();
  }
  clear_has_auction_goods();
}
inline const ::std::string& DailyAuctionConfigProto::auction_goods() const {
  return *auction_goods_;
}
inline void DailyAuctionConfigProto::set_auction_goods(const ::std::string& value) {
  set_has_auction_goods();
  if (auction_goods_ == &::google::protobuf::internal::kEmptyString) {
    auction_goods_ = new ::std::string;
  }
  auction_goods_->assign(value);
}
inline void DailyAuctionConfigProto::set_auction_goods(const char* value) {
  set_has_auction_goods();
  if (auction_goods_ == &::google::protobuf::internal::kEmptyString) {
    auction_goods_ = new ::std::string;
  }
  auction_goods_->assign(value);
}
inline void DailyAuctionConfigProto::set_auction_goods(const void* value, size_t size) {
  set_has_auction_goods();
  if (auction_goods_ == &::google::protobuf::internal::kEmptyString) {
    auction_goods_ = new ::std::string;
  }
  auction_goods_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* DailyAuctionConfigProto::mutable_auction_goods() {
  set_has_auction_goods();
  if (auction_goods_ == &::google::protobuf::internal::kEmptyString) {
    auction_goods_ = new ::std::string;
  }
  return auction_goods_;
}
inline ::std::string* DailyAuctionConfigProto::release_auction_goods() {
  clear_has_auction_goods();
  if (auction_goods_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = auction_goods_;
    auction_goods_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void DailyAuctionConfigProto::set_allocated_auction_goods(::std::string* auction_goods) {
  if (auction_goods_ != &::google::protobuf::internal::kEmptyString) {
    delete auction_goods_;
  }
  if (auction_goods) {
    set_has_auction_goods();
    auction_goods_ = auction_goods;
  } else {
    clear_has_auction_goods();
    auction_goods_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// optional int32 yuanbao_price = 5;
inline bool DailyAuctionConfigProto::has_yuanbao_price() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void DailyAuctionConfigProto::set_has_yuanbao_price() {
  _has_bits_[0] |= 0x00000010u;
}
inline void DailyAuctionConfigProto::clear_has_yuanbao_price() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void DailyAuctionConfigProto::clear_yuanbao_price() {
  yuanbao_price_ = 0;
  clear_has_yuanbao_price();
}
inline ::google::protobuf::int32 DailyAuctionConfigProto::yuanbao_price() const {
  return yuanbao_price_;
}
inline void DailyAuctionConfigProto::set_yuanbao_price(::google::protobuf::int32 value) {
  set_has_yuanbao_price();
  yuanbao_price_ = value;
}

// -------------------------------------------------------------------

// SingleDailyAuctionConfig

// optional int32 id = 1;
inline bool SingleDailyAuctionConfig::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void SingleDailyAuctionConfig::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void SingleDailyAuctionConfig::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void SingleDailyAuctionConfig::clear_id() {
  id_ = 0;
  clear_has_id();
}
inline ::google::protobuf::int32 SingleDailyAuctionConfig::id() const {
  return id_;
}
inline void SingleDailyAuctionConfig::set_id(::google::protobuf::int32 value) {
  set_has_id();
  id_ = value;
}

// optional bytes desc = 2;
inline bool SingleDailyAuctionConfig::has_desc() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void SingleDailyAuctionConfig::set_has_desc() {
  _has_bits_[0] |= 0x00000002u;
}
inline void SingleDailyAuctionConfig::clear_has_desc() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void SingleDailyAuctionConfig::clear_desc() {
  if (desc_ != &::google::protobuf::internal::kEmptyString) {
    desc_->clear();
  }
  clear_has_desc();
}
inline const ::std::string& SingleDailyAuctionConfig::desc() const {
  return *desc_;
}
inline void SingleDailyAuctionConfig::set_desc(const ::std::string& value) {
  set_has_desc();
  if (desc_ == &::google::protobuf::internal::kEmptyString) {
    desc_ = new ::std::string;
  }
  desc_->assign(value);
}
inline void SingleDailyAuctionConfig::set_desc(const char* value) {
  set_has_desc();
  if (desc_ == &::google::protobuf::internal::kEmptyString) {
    desc_ = new ::std::string;
  }
  desc_->assign(value);
}
inline void SingleDailyAuctionConfig::set_desc(const void* value, size_t size) {
  set_has_desc();
  if (desc_ == &::google::protobuf::internal::kEmptyString) {
    desc_ = new ::std::string;
  }
  desc_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* SingleDailyAuctionConfig::mutable_desc() {
  set_has_desc();
  if (desc_ == &::google::protobuf::internal::kEmptyString) {
    desc_ = new ::std::string;
  }
  return desc_;
}
inline ::std::string* SingleDailyAuctionConfig::release_desc() {
  clear_has_desc();
  if (desc_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = desc_;
    desc_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void SingleDailyAuctionConfig::set_allocated_desc(::std::string* desc) {
  if (desc_ != &::google::protobuf::internal::kEmptyString) {
    delete desc_;
  }
  if (desc) {
    set_has_desc();
    desc_ = desc;
  } else {
    clear_has_desc();
    desc_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// optional int32 minYuanbao = 3 [deprecated = true];
inline bool SingleDailyAuctionConfig::has_minyuanbao() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void SingleDailyAuctionConfig::set_has_minyuanbao() {
  _has_bits_[0] |= 0x00000004u;
}
inline void SingleDailyAuctionConfig::clear_has_minyuanbao() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void SingleDailyAuctionConfig::clear_minyuanbao() {
  minyuanbao_ = 0;
  clear_has_minyuanbao();
}
inline ::google::protobuf::int32 SingleDailyAuctionConfig::minyuanbao() const {
  return minyuanbao_;
}
inline void SingleDailyAuctionConfig::set_minyuanbao(::google::protobuf::int32 value) {
  set_has_minyuanbao();
  minyuanbao_ = value;
}

// optional .app.message.GoodsWrapperProto prize = 4;
inline bool SingleDailyAuctionConfig::has_prize() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void SingleDailyAuctionConfig::set_has_prize() {
  _has_bits_[0] |= 0x00000008u;
}
inline void SingleDailyAuctionConfig::clear_has_prize() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void SingleDailyAuctionConfig::clear_prize() {
  if (prize_ != NULL) prize_->::app::message::GoodsWrapperProto::Clear();
  clear_has_prize();
}
inline const ::app::message::GoodsWrapperProto& SingleDailyAuctionConfig::prize() const {
  return prize_ != NULL ? *prize_ : *default_instance_->prize_;
}
inline ::app::message::GoodsWrapperProto* SingleDailyAuctionConfig::mutable_prize() {
  set_has_prize();
  if (prize_ == NULL) prize_ = new ::app::message::GoodsWrapperProto;
  return prize_;
}
inline ::app::message::GoodsWrapperProto* SingleDailyAuctionConfig::release_prize() {
  clear_has_prize();
  ::app::message::GoodsWrapperProto* temp = prize_;
  prize_ = NULL;
  return temp;
}
inline void SingleDailyAuctionConfig::set_allocated_prize(::app::message::GoodsWrapperProto* prize) {
  delete prize_;
  prize_ = prize;
  if (prize) {
    set_has_prize();
  } else {
    clear_has_prize();
  }
}

// optional int32 min_auction_goods = 5;
inline bool SingleDailyAuctionConfig::has_min_auction_goods() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void SingleDailyAuctionConfig::set_has_min_auction_goods() {
  _has_bits_[0] |= 0x00000010u;
}
inline void SingleDailyAuctionConfig::clear_has_min_auction_goods() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void SingleDailyAuctionConfig::clear_min_auction_goods() {
  min_auction_goods_ = 0;
  clear_has_min_auction_goods();
}
inline ::google::protobuf::int32 SingleDailyAuctionConfig::min_auction_goods() const {
  return min_auction_goods_;
}
inline void SingleDailyAuctionConfig::set_min_auction_goods(::google::protobuf::int32 value) {
  set_has_min_auction_goods();
  min_auction_goods_ = value;
}

// -------------------------------------------------------------------

// GlobalAuctionData

// repeated int32 id = 1;
inline int GlobalAuctionData::id_size() const {
  return id_.size();
}
inline void GlobalAuctionData::clear_id() {
  id_.Clear();
}
inline ::google::protobuf::int32 GlobalAuctionData::id(int index) const {
  return id_.Get(index);
}
inline void GlobalAuctionData::set_id(int index, ::google::protobuf::int32 value) {
  id_.Set(index, value);
}
inline void GlobalAuctionData::add_id(::google::protobuf::int32 value) {
  id_.Add(value);
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::int32 >&
GlobalAuctionData::id() const {
  return id_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::int32 >*
GlobalAuctionData::mutable_id() {
  return &id_;
}

// repeated int64 herod_id = 2;
inline int GlobalAuctionData::herod_id_size() const {
  return herod_id_.size();
}
inline void GlobalAuctionData::clear_herod_id() {
  herod_id_.Clear();
}
inline ::google::protobuf::int64 GlobalAuctionData::herod_id(int index) const {
  return herod_id_.Get(index);
}
inline void GlobalAuctionData::set_herod_id(int index, ::google::protobuf::int64 value) {
  herod_id_.Set(index, value);
}
inline void GlobalAuctionData::add_herod_id(::google::protobuf::int64 value) {
  herod_id_.Add(value);
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::int64 >&
GlobalAuctionData::herod_id() const {
  return herod_id_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::int64 >*
GlobalAuctionData::mutable_herod_id() {
  return &herod_id_;
}

// repeated bytes hero_name = 3;
inline int GlobalAuctionData::hero_name_size() const {
  return hero_name_.size();
}
inline void GlobalAuctionData::clear_hero_name() {
  hero_name_.Clear();
}
inline const ::std::string& GlobalAuctionData::hero_name(int index) const {
  return hero_name_.Get(index);
}
inline ::std::string* GlobalAuctionData::mutable_hero_name(int index) {
  return hero_name_.Mutable(index);
}
inline void GlobalAuctionData::set_hero_name(int index, const ::std::string& value) {
  hero_name_.Mutable(index)->assign(value);
}
inline void GlobalAuctionData::set_hero_name(int index, const char* value) {
  hero_name_.Mutable(index)->assign(value);
}
inline void GlobalAuctionData::set_hero_name(int index, const void* value, size_t size) {
  hero_name_.Mutable(index)->assign(
    reinterpret_cast<const char*>(value), size);
}
inline ::std::string* GlobalAuctionData::add_hero_name() {
  return hero_name_.Add();
}
inline void GlobalAuctionData::add_hero_name(const ::std::string& value) {
  hero_name_.Add()->assign(value);
}
inline void GlobalAuctionData::add_hero_name(const char* value) {
  hero_name_.Add()->assign(value);
}
inline void GlobalAuctionData::add_hero_name(const void* value, size_t size) {
  hero_name_.Add()->assign(reinterpret_cast<const char*>(value), size);
}
inline const ::google::protobuf::RepeatedPtrField< ::std::string>&
GlobalAuctionData::hero_name() const {
  return hero_name_;
}
inline ::google::protobuf::RepeatedPtrField< ::std::string>*
GlobalAuctionData::mutable_hero_name() {
  return &hero_name_;
}

// repeated int32 current_max_yuanbao = 4 [deprecated = true];
inline int GlobalAuctionData::current_max_yuanbao_size() const {
  return current_max_yuanbao_.size();
}
inline void GlobalAuctionData::clear_current_max_yuanbao() {
  current_max_yuanbao_.Clear();
}
inline ::google::protobuf::int32 GlobalAuctionData::current_max_yuanbao(int index) const {
  return current_max_yuanbao_.Get(index);
}
inline void GlobalAuctionData::set_current_max_yuanbao(int index, ::google::protobuf::int32 value) {
  current_max_yuanbao_.Set(index, value);
}
inline void GlobalAuctionData::add_current_max_yuanbao(::google::protobuf::int32 value) {
  current_max_yuanbao_.Add(value);
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::int32 >&
GlobalAuctionData::current_max_yuanbao() const {
  return current_max_yuanbao_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::int32 >*
GlobalAuctionData::mutable_current_max_yuanbao() {
  return &current_max_yuanbao_;
}

// repeated int32 current_max_price = 5;
inline int GlobalAuctionData::current_max_price_size() const {
  return current_max_price_.size();
}
inline void GlobalAuctionData::clear_current_max_price() {
  current_max_price_.Clear();
}
inline ::google::protobuf::int32 GlobalAuctionData::current_max_price(int index) const {
  return current_max_price_.Get(index);
}
inline void GlobalAuctionData::set_current_max_price(int index, ::google::protobuf::int32 value) {
  current_max_price_.Set(index, value);
}
inline void GlobalAuctionData::add_current_max_price(::google::protobuf::int32 value) {
  current_max_price_.Add(value);
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::int32 >&
GlobalAuctionData::current_max_price() const {
  return current_max_price_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::int32 >*
GlobalAuctionData::mutable_current_max_price() {
  return &current_max_price_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace message
}  // namespace app

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_daily_5fauction_2eproto__INCLUDED
