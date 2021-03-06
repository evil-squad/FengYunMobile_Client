// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: daily_lucky_wheel.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "daily_lucky_wheel.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace app {
namespace message {

namespace {

const ::google::protobuf::Descriptor* DailyLuckyWheelPrizeInfoProto_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  DailyLuckyWheelPrizeInfoProto_reflection_ = NULL;
const ::google::protobuf::Descriptor* DailyLuckyWheelConfig_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  DailyLuckyWheelConfig_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_daily_5flucky_5fwheel_2eproto() {
  protobuf_AddDesc_daily_5flucky_5fwheel_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "daily_lucky_wheel.proto");
  GOOGLE_CHECK(file != NULL);
  DailyLuckyWheelPrizeInfoProto_descriptor_ = file->message_type(0);
  static const int DailyLuckyWheelPrizeInfoProto_offsets_[7] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(DailyLuckyWheelPrizeInfoProto, id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(DailyLuckyWheelPrizeInfoProto, name_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(DailyLuckyWheelPrizeInfoProto, desc_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(DailyLuckyWheelPrizeInfoProto, icon_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(DailyLuckyWheelPrizeInfoProto, quality_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(DailyLuckyWheelPrizeInfoProto, count_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(DailyLuckyWheelPrizeInfoProto, game_object_),
  };
  DailyLuckyWheelPrizeInfoProto_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      DailyLuckyWheelPrizeInfoProto_descriptor_,
      DailyLuckyWheelPrizeInfoProto::default_instance_,
      DailyLuckyWheelPrizeInfoProto_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(DailyLuckyWheelPrizeInfoProto, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(DailyLuckyWheelPrizeInfoProto, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(DailyLuckyWheelPrizeInfoProto));
  DailyLuckyWheelConfig_descriptor_ = file->message_type(1);
  static const int DailyLuckyWheelConfig_offsets_[5] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(DailyLuckyWheelConfig, log_max_count_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(DailyLuckyWheelConfig, prize_infos_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(DailyLuckyWheelConfig, start_time_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(DailyLuckyWheelConfig, end_time_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(DailyLuckyWheelConfig, daily_times_),
  };
  DailyLuckyWheelConfig_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      DailyLuckyWheelConfig_descriptor_,
      DailyLuckyWheelConfig::default_instance_,
      DailyLuckyWheelConfig_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(DailyLuckyWheelConfig, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(DailyLuckyWheelConfig, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(DailyLuckyWheelConfig));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_daily_5flucky_5fwheel_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    DailyLuckyWheelPrizeInfoProto_descriptor_, &DailyLuckyWheelPrizeInfoProto::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    DailyLuckyWheelConfig_descriptor_, &DailyLuckyWheelConfig::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_daily_5flucky_5fwheel_2eproto() {
  delete DailyLuckyWheelPrizeInfoProto::default_instance_;
  delete DailyLuckyWheelPrizeInfoProto_reflection_;
  delete DailyLuckyWheelConfig::default_instance_;
  delete DailyLuckyWheelConfig_reflection_;
}

void protobuf_AddDesc_daily_5flucky_5fwheel_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::app::message::protobuf_AddDesc_goods_2eproto();
  ::app::message::protobuf_AddDesc_config_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\027daily_lucky_wheel.proto\022\013app.message\032\013"
    "goods.proto\032\014config.proto\"\212\001\n\035DailyLucky"
    "WheelPrizeInfoProto\022\n\n\002id\030\001 \001(\005\022\014\n\004name\030"
    "\002 \001(\014\022\014\n\004desc\030\003 \001(\014\022\014\n\004icon\030\004 \001(\t\022\017\n\007qua"
    "lity\030\005 \001(\005\022\r\n\005count\030\006 \001(\005\022\023\n\013game_object"
    "\030\007 \001(\010\"\252\001\n\025DailyLuckyWheelConfig\022\025\n\rlog_"
    "max_count\030\001 \001(\005\022\?\n\013prize_infos\030\002 \003(\0132*.a"
    "pp.message.DailyLuckyWheelPrizeInfoProto"
    "\022\022\n\nstart_time\030\003 \001(\003\022\020\n\010end_time\030\004 \001(\003\022\023"
    "\n\013daily_times\030\005 \001(\005B(\n\014app.protobufB\026Dai"
    "lyLuckyWheelContentH\001", 421);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "daily_lucky_wheel.proto", &protobuf_RegisterTypes);
  DailyLuckyWheelPrizeInfoProto::default_instance_ = new DailyLuckyWheelPrizeInfoProto();
  DailyLuckyWheelConfig::default_instance_ = new DailyLuckyWheelConfig();
  DailyLuckyWheelPrizeInfoProto::default_instance_->InitAsDefaultInstance();
  DailyLuckyWheelConfig::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_daily_5flucky_5fwheel_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_daily_5flucky_5fwheel_2eproto {
  StaticDescriptorInitializer_daily_5flucky_5fwheel_2eproto() {
    protobuf_AddDesc_daily_5flucky_5fwheel_2eproto();
  }
} static_descriptor_initializer_daily_5flucky_5fwheel_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int DailyLuckyWheelPrizeInfoProto::kIdFieldNumber;
const int DailyLuckyWheelPrizeInfoProto::kNameFieldNumber;
const int DailyLuckyWheelPrizeInfoProto::kDescFieldNumber;
const int DailyLuckyWheelPrizeInfoProto::kIconFieldNumber;
const int DailyLuckyWheelPrizeInfoProto::kQualityFieldNumber;
const int DailyLuckyWheelPrizeInfoProto::kCountFieldNumber;
const int DailyLuckyWheelPrizeInfoProto::kGameObjectFieldNumber;
#endif  // !_MSC_VER

DailyLuckyWheelPrizeInfoProto::DailyLuckyWheelPrizeInfoProto()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void DailyLuckyWheelPrizeInfoProto::InitAsDefaultInstance() {
}

DailyLuckyWheelPrizeInfoProto::DailyLuckyWheelPrizeInfoProto(const DailyLuckyWheelPrizeInfoProto& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void DailyLuckyWheelPrizeInfoProto::SharedCtor() {
  _cached_size_ = 0;
  id_ = 0;
  name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  desc_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  icon_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  quality_ = 0;
  count_ = 0;
  game_object_ = false;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

DailyLuckyWheelPrizeInfoProto::~DailyLuckyWheelPrizeInfoProto() {
  SharedDtor();
}

void DailyLuckyWheelPrizeInfoProto::SharedDtor() {
  if (name_ != &::google::protobuf::internal::kEmptyString) {
    delete name_;
  }
  if (desc_ != &::google::protobuf::internal::kEmptyString) {
    delete desc_;
  }
  if (icon_ != &::google::protobuf::internal::kEmptyString) {
    delete icon_;
  }
  if (this != default_instance_) {
  }
}

void DailyLuckyWheelPrizeInfoProto::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* DailyLuckyWheelPrizeInfoProto::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return DailyLuckyWheelPrizeInfoProto_descriptor_;
}

const DailyLuckyWheelPrizeInfoProto& DailyLuckyWheelPrizeInfoProto::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_daily_5flucky_5fwheel_2eproto();
  return *default_instance_;
}

DailyLuckyWheelPrizeInfoProto* DailyLuckyWheelPrizeInfoProto::default_instance_ = NULL;

DailyLuckyWheelPrizeInfoProto* DailyLuckyWheelPrizeInfoProto::New() const {
  return new DailyLuckyWheelPrizeInfoProto;
}

void DailyLuckyWheelPrizeInfoProto::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    id_ = 0;
    if (has_name()) {
      if (name_ != &::google::protobuf::internal::kEmptyString) {
        name_->clear();
      }
    }
    if (has_desc()) {
      if (desc_ != &::google::protobuf::internal::kEmptyString) {
        desc_->clear();
      }
    }
    if (has_icon()) {
      if (icon_ != &::google::protobuf::internal::kEmptyString) {
        icon_->clear();
      }
    }
    quality_ = 0;
    count_ = 0;
    game_object_ = false;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool DailyLuckyWheelPrizeInfoProto::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional int32 id = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &id_)));
          set_has_id();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(18)) goto parse_name;
        break;
      }

      // optional bytes name = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_name:
          DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                input, this->mutable_name()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(26)) goto parse_desc;
        break;
      }

      // optional bytes desc = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_desc:
          DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                input, this->mutable_desc()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(34)) goto parse_icon;
        break;
      }

      // optional string icon = 4;
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_icon:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_icon()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->icon().data(), this->icon().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(40)) goto parse_quality;
        break;
      }

      // optional int32 quality = 5;
      case 5: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_quality:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &quality_)));
          set_has_quality();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(48)) goto parse_count;
        break;
      }

      // optional int32 count = 6;
      case 6: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_count:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &count_)));
          set_has_count();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(56)) goto parse_game_object;
        break;
      }

      // optional bool game_object = 7;
      case 7: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_game_object:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &game_object_)));
          set_has_game_object();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }

      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void DailyLuckyWheelPrizeInfoProto::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional int32 id = 1;
  if (has_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->id(), output);
  }

  // optional bytes name = 2;
  if (has_name()) {
    ::google::protobuf::internal::WireFormatLite::WriteBytes(
      2, this->name(), output);
  }

  // optional bytes desc = 3;
  if (has_desc()) {
    ::google::protobuf::internal::WireFormatLite::WriteBytes(
      3, this->desc(), output);
  }

  // optional string icon = 4;
  if (has_icon()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->icon().data(), this->icon().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      4, this->icon(), output);
  }

  // optional int32 quality = 5;
  if (has_quality()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(5, this->quality(), output);
  }

  // optional int32 count = 6;
  if (has_count()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(6, this->count(), output);
  }

  // optional bool game_object = 7;
  if (has_game_object()) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(7, this->game_object(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* DailyLuckyWheelPrizeInfoProto::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional int32 id = 1;
  if (has_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->id(), target);
  }

  // optional bytes name = 2;
  if (has_name()) {
    target =
      ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
        2, this->name(), target);
  }

  // optional bytes desc = 3;
  if (has_desc()) {
    target =
      ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
        3, this->desc(), target);
  }

  // optional string icon = 4;
  if (has_icon()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->icon().data(), this->icon().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        4, this->icon(), target);
  }

  // optional int32 quality = 5;
  if (has_quality()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(5, this->quality(), target);
  }

  // optional int32 count = 6;
  if (has_count()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(6, this->count(), target);
  }

  // optional bool game_object = 7;
  if (has_game_object()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(7, this->game_object(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int DailyLuckyWheelPrizeInfoProto::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional int32 id = 1;
    if (has_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->id());
    }

    // optional bytes name = 2;
    if (has_name()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::BytesSize(
          this->name());
    }

    // optional bytes desc = 3;
    if (has_desc()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::BytesSize(
          this->desc());
    }

    // optional string icon = 4;
    if (has_icon()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->icon());
    }

    // optional int32 quality = 5;
    if (has_quality()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->quality());
    }

    // optional int32 count = 6;
    if (has_count()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->count());
    }

    // optional bool game_object = 7;
    if (has_game_object()) {
      total_size += 1 + 1;
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void DailyLuckyWheelPrizeInfoProto::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const DailyLuckyWheelPrizeInfoProto* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const DailyLuckyWheelPrizeInfoProto*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void DailyLuckyWheelPrizeInfoProto::MergeFrom(const DailyLuckyWheelPrizeInfoProto& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_id()) {
      set_id(from.id());
    }
    if (from.has_name()) {
      set_name(from.name());
    }
    if (from.has_desc()) {
      set_desc(from.desc());
    }
    if (from.has_icon()) {
      set_icon(from.icon());
    }
    if (from.has_quality()) {
      set_quality(from.quality());
    }
    if (from.has_count()) {
      set_count(from.count());
    }
    if (from.has_game_object()) {
      set_game_object(from.game_object());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void DailyLuckyWheelPrizeInfoProto::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void DailyLuckyWheelPrizeInfoProto::CopyFrom(const DailyLuckyWheelPrizeInfoProto& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool DailyLuckyWheelPrizeInfoProto::IsInitialized() const {

  return true;
}

void DailyLuckyWheelPrizeInfoProto::Swap(DailyLuckyWheelPrizeInfoProto* other) {
  if (other != this) {
    std::swap(id_, other->id_);
    std::swap(name_, other->name_);
    std::swap(desc_, other->desc_);
    std::swap(icon_, other->icon_);
    std::swap(quality_, other->quality_);
    std::swap(count_, other->count_);
    std::swap(game_object_, other->game_object_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata DailyLuckyWheelPrizeInfoProto::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = DailyLuckyWheelPrizeInfoProto_descriptor_;
  metadata.reflection = DailyLuckyWheelPrizeInfoProto_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int DailyLuckyWheelConfig::kLogMaxCountFieldNumber;
const int DailyLuckyWheelConfig::kPrizeInfosFieldNumber;
const int DailyLuckyWheelConfig::kStartTimeFieldNumber;
const int DailyLuckyWheelConfig::kEndTimeFieldNumber;
const int DailyLuckyWheelConfig::kDailyTimesFieldNumber;
#endif  // !_MSC_VER

DailyLuckyWheelConfig::DailyLuckyWheelConfig()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void DailyLuckyWheelConfig::InitAsDefaultInstance() {
}

DailyLuckyWheelConfig::DailyLuckyWheelConfig(const DailyLuckyWheelConfig& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void DailyLuckyWheelConfig::SharedCtor() {
  _cached_size_ = 0;
  log_max_count_ = 0;
  start_time_ = GOOGLE_LONGLONG(0);
  end_time_ = GOOGLE_LONGLONG(0);
  daily_times_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

DailyLuckyWheelConfig::~DailyLuckyWheelConfig() {
  SharedDtor();
}

void DailyLuckyWheelConfig::SharedDtor() {
  if (this != default_instance_) {
  }
}

void DailyLuckyWheelConfig::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* DailyLuckyWheelConfig::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return DailyLuckyWheelConfig_descriptor_;
}

const DailyLuckyWheelConfig& DailyLuckyWheelConfig::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_daily_5flucky_5fwheel_2eproto();
  return *default_instance_;
}

DailyLuckyWheelConfig* DailyLuckyWheelConfig::default_instance_ = NULL;

DailyLuckyWheelConfig* DailyLuckyWheelConfig::New() const {
  return new DailyLuckyWheelConfig;
}

void DailyLuckyWheelConfig::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    log_max_count_ = 0;
    start_time_ = GOOGLE_LONGLONG(0);
    end_time_ = GOOGLE_LONGLONG(0);
    daily_times_ = 0;
  }
  prize_infos_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool DailyLuckyWheelConfig::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional int32 log_max_count = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &log_max_count_)));
          set_has_log_max_count();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(18)) goto parse_prize_infos;
        break;
      }

      // repeated .app.message.DailyLuckyWheelPrizeInfoProto prize_infos = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_prize_infos:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_prize_infos()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(18)) goto parse_prize_infos;
        if (input->ExpectTag(24)) goto parse_start_time;
        break;
      }

      // optional int64 start_time = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_start_time:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_INT64>(
                 input, &start_time_)));
          set_has_start_time();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(32)) goto parse_end_time;
        break;
      }

      // optional int64 end_time = 4;
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_end_time:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_INT64>(
                 input, &end_time_)));
          set_has_end_time();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(40)) goto parse_daily_times;
        break;
      }

      // optional int32 daily_times = 5;
      case 5: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_daily_times:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &daily_times_)));
          set_has_daily_times();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }

      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void DailyLuckyWheelConfig::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional int32 log_max_count = 1;
  if (has_log_max_count()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->log_max_count(), output);
  }

  // repeated .app.message.DailyLuckyWheelPrizeInfoProto prize_infos = 2;
  for (int i = 0; i < this->prize_infos_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      2, this->prize_infos(i), output);
  }

  // optional int64 start_time = 3;
  if (has_start_time()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt64(3, this->start_time(), output);
  }

  // optional int64 end_time = 4;
  if (has_end_time()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt64(4, this->end_time(), output);
  }

  // optional int32 daily_times = 5;
  if (has_daily_times()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(5, this->daily_times(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* DailyLuckyWheelConfig::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional int32 log_max_count = 1;
  if (has_log_max_count()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->log_max_count(), target);
  }

  // repeated .app.message.DailyLuckyWheelPrizeInfoProto prize_infos = 2;
  for (int i = 0; i < this->prize_infos_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        2, this->prize_infos(i), target);
  }

  // optional int64 start_time = 3;
  if (has_start_time()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt64ToArray(3, this->start_time(), target);
  }

  // optional int64 end_time = 4;
  if (has_end_time()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt64ToArray(4, this->end_time(), target);
  }

  // optional int32 daily_times = 5;
  if (has_daily_times()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(5, this->daily_times(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int DailyLuckyWheelConfig::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional int32 log_max_count = 1;
    if (has_log_max_count()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->log_max_count());
    }

    // optional int64 start_time = 3;
    if (has_start_time()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int64Size(
          this->start_time());
    }

    // optional int64 end_time = 4;
    if (has_end_time()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int64Size(
          this->end_time());
    }

    // optional int32 daily_times = 5;
    if (has_daily_times()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->daily_times());
    }

  }
  // repeated .app.message.DailyLuckyWheelPrizeInfoProto prize_infos = 2;
  total_size += 1 * this->prize_infos_size();
  for (int i = 0; i < this->prize_infos_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->prize_infos(i));
  }

  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void DailyLuckyWheelConfig::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const DailyLuckyWheelConfig* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const DailyLuckyWheelConfig*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void DailyLuckyWheelConfig::MergeFrom(const DailyLuckyWheelConfig& from) {
  GOOGLE_CHECK_NE(&from, this);
  prize_infos_.MergeFrom(from.prize_infos_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_log_max_count()) {
      set_log_max_count(from.log_max_count());
    }
    if (from.has_start_time()) {
      set_start_time(from.start_time());
    }
    if (from.has_end_time()) {
      set_end_time(from.end_time());
    }
    if (from.has_daily_times()) {
      set_daily_times(from.daily_times());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void DailyLuckyWheelConfig::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void DailyLuckyWheelConfig::CopyFrom(const DailyLuckyWheelConfig& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool DailyLuckyWheelConfig::IsInitialized() const {

  return true;
}

void DailyLuckyWheelConfig::Swap(DailyLuckyWheelConfig* other) {
  if (other != this) {
    std::swap(log_max_count_, other->log_max_count_);
    prize_infos_.Swap(&other->prize_infos_);
    std::swap(start_time_, other->start_time_);
    std::swap(end_time_, other->end_time_);
    std::swap(daily_times_, other->daily_times_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata DailyLuckyWheelConfig::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = DailyLuckyWheelConfig_descriptor_;
  metadata.reflection = DailyLuckyWheelConfig_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace message
}  // namespace app

// @@protoc_insertion_point(global_scope)
