// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: game.proto

#ifndef PROTOBUF_INCLUDED_game_2eproto
#define PROTOBUF_INCLUDED_game_2eproto

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3006001
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3006001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#define PROTOBUF_INTERNAL_EXPORT_protobuf_game_2eproto 

namespace protobuf_game_2eproto {
// Internal implementation detail -- do not use these members.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[5];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors();
}  // namespace protobuf_game_2eproto
namespace moba {
class FrameData;
class FrameDataDefaultTypeInternal;
extern FrameDataDefaultTypeInternal _FrameData_default_instance_;
class GameState;
class GameStateDefaultTypeInternal;
extern GameStateDefaultTypeInternal _GameState_default_instance_;
class Player;
class PlayerDefaultTypeInternal;
extern PlayerDefaultTypeInternal _Player_default_instance_;
class PlayerInput;
class PlayerInputDefaultTypeInternal;
extern PlayerInputDefaultTypeInternal _PlayerInput_default_instance_;
class Vector3;
class Vector3DefaultTypeInternal;
extern Vector3DefaultTypeInternal _Vector3_default_instance_;
}  // namespace moba
namespace google {
namespace protobuf {
template<> ::moba::FrameData* Arena::CreateMaybeMessage<::moba::FrameData>(Arena*);
template<> ::moba::GameState* Arena::CreateMaybeMessage<::moba::GameState>(Arena*);
template<> ::moba::Player* Arena::CreateMaybeMessage<::moba::Player>(Arena*);
template<> ::moba::PlayerInput* Arena::CreateMaybeMessage<::moba::PlayerInput>(Arena*);
template<> ::moba::Vector3* Arena::CreateMaybeMessage<::moba::Vector3>(Arena*);
}  // namespace protobuf
}  // namespace google
namespace moba {

// ===================================================================

class PlayerInput : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:moba.PlayerInput) */ {
 public:
  PlayerInput();
  virtual ~PlayerInput();

  PlayerInput(const PlayerInput& from);

  inline PlayerInput& operator=(const PlayerInput& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  PlayerInput(PlayerInput&& from) noexcept
    : PlayerInput() {
    *this = ::std::move(from);
  }

  inline PlayerInput& operator=(PlayerInput&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const PlayerInput& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const PlayerInput* internal_default_instance() {
    return reinterpret_cast<const PlayerInput*>(
               &_PlayerInput_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(PlayerInput* other);
  friend void swap(PlayerInput& a, PlayerInput& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline PlayerInput* New() const final {
    return CreateMaybeMessage<PlayerInput>(NULL);
  }

  PlayerInput* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<PlayerInput>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const PlayerInput& from);
  void MergeFrom(const PlayerInput& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(PlayerInput* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // repeated uint32 skills = 4;
  int skills_size() const;
  void clear_skills();
  static const int kSkillsFieldNumber = 4;
  ::google::protobuf::uint32 skills(int index) const;
  void set_skills(int index, ::google::protobuf::uint32 value);
  void add_skills(::google::protobuf::uint32 value);
  const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
      skills() const;
  ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
      mutable_skills();

  // .moba.Vector3 move_dir = 3;
  bool has_move_dir() const;
  void clear_move_dir();
  static const int kMoveDirFieldNumber = 3;
  private:
  const ::moba::Vector3& _internal_move_dir() const;
  public:
  const ::moba::Vector3& move_dir() const;
  ::moba::Vector3* release_move_dir();
  ::moba::Vector3* mutable_move_dir();
  void set_allocated_move_dir(::moba::Vector3* move_dir);

  // uint32 player_id = 1;
  void clear_player_id();
  static const int kPlayerIdFieldNumber = 1;
  ::google::protobuf::uint32 player_id() const;
  void set_player_id(::google::protobuf::uint32 value);

  // uint32 frame_num = 2;
  void clear_frame_num();
  static const int kFrameNumFieldNumber = 2;
  ::google::protobuf::uint32 frame_num() const;
  void set_frame_num(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:moba.PlayerInput)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::RepeatedField< ::google::protobuf::uint32 > skills_;
  mutable int _skills_cached_byte_size_;
  ::moba::Vector3* move_dir_;
  ::google::protobuf::uint32 player_id_;
  ::google::protobuf::uint32 frame_num_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::protobuf_game_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class Vector3 : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:moba.Vector3) */ {
 public:
  Vector3();
  virtual ~Vector3();

  Vector3(const Vector3& from);

  inline Vector3& operator=(const Vector3& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Vector3(Vector3&& from) noexcept
    : Vector3() {
    *this = ::std::move(from);
  }

  inline Vector3& operator=(Vector3&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const Vector3& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Vector3* internal_default_instance() {
    return reinterpret_cast<const Vector3*>(
               &_Vector3_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  void Swap(Vector3* other);
  friend void swap(Vector3& a, Vector3& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Vector3* New() const final {
    return CreateMaybeMessage<Vector3>(NULL);
  }

  Vector3* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<Vector3>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const Vector3& from);
  void MergeFrom(const Vector3& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Vector3* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // float x = 1;
  void clear_x();
  static const int kXFieldNumber = 1;
  float x() const;
  void set_x(float value);

  // float y = 2;
  void clear_y();
  static const int kYFieldNumber = 2;
  float y() const;
  void set_y(float value);

  // float z = 3;
  void clear_z();
  static const int kZFieldNumber = 3;
  float z() const;
  void set_z(float value);

  // @@protoc_insertion_point(class_scope:moba.Vector3)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  float x_;
  float y_;
  float z_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::protobuf_game_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class FrameData : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:moba.FrameData) */ {
 public:
  FrameData();
  virtual ~FrameData();

  FrameData(const FrameData& from);

  inline FrameData& operator=(const FrameData& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  FrameData(FrameData&& from) noexcept
    : FrameData() {
    *this = ::std::move(from);
  }

  inline FrameData& operator=(FrameData&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const FrameData& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const FrameData* internal_default_instance() {
    return reinterpret_cast<const FrameData*>(
               &_FrameData_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    2;

  void Swap(FrameData* other);
  friend void swap(FrameData& a, FrameData& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline FrameData* New() const final {
    return CreateMaybeMessage<FrameData>(NULL);
  }

  FrameData* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<FrameData>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const FrameData& from);
  void MergeFrom(const FrameData& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(FrameData* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // repeated .moba.PlayerInput inputs = 2;
  int inputs_size() const;
  void clear_inputs();
  static const int kInputsFieldNumber = 2;
  ::moba::PlayerInput* mutable_inputs(int index);
  ::google::protobuf::RepeatedPtrField< ::moba::PlayerInput >*
      mutable_inputs();
  const ::moba::PlayerInput& inputs(int index) const;
  ::moba::PlayerInput* add_inputs();
  const ::google::protobuf::RepeatedPtrField< ::moba::PlayerInput >&
      inputs() const;

  // uint32 frame_num = 1;
  void clear_frame_num();
  static const int kFrameNumFieldNumber = 1;
  ::google::protobuf::uint32 frame_num() const;
  void set_frame_num(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:moba.FrameData)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::RepeatedPtrField< ::moba::PlayerInput > inputs_;
  ::google::protobuf::uint32 frame_num_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::protobuf_game_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class GameState : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:moba.GameState) */ {
 public:
  GameState();
  virtual ~GameState();

  GameState(const GameState& from);

  inline GameState& operator=(const GameState& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  GameState(GameState&& from) noexcept
    : GameState() {
    *this = ::std::move(from);
  }

  inline GameState& operator=(GameState&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const GameState& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const GameState* internal_default_instance() {
    return reinterpret_cast<const GameState*>(
               &_GameState_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    3;

  void Swap(GameState* other);
  friend void swap(GameState& a, GameState& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline GameState* New() const final {
    return CreateMaybeMessage<GameState>(NULL);
  }

  GameState* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<GameState>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const GameState& from);
  void MergeFrom(const GameState& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(GameState* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // repeated .moba.Player players = 1;
  int players_size() const;
  void clear_players();
  static const int kPlayersFieldNumber = 1;
  ::moba::Player* mutable_players(int index);
  ::google::protobuf::RepeatedPtrField< ::moba::Player >*
      mutable_players();
  const ::moba::Player& players(int index) const;
  ::moba::Player* add_players();
  const ::google::protobuf::RepeatedPtrField< ::moba::Player >&
      players() const;

  // uint32 current_frame = 2;
  void clear_current_frame();
  static const int kCurrentFrameFieldNumber = 2;
  ::google::protobuf::uint32 current_frame() const;
  void set_current_frame(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:moba.GameState)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::RepeatedPtrField< ::moba::Player > players_;
  ::google::protobuf::uint32 current_frame_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::protobuf_game_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class Player : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:moba.Player) */ {
 public:
  Player();
  virtual ~Player();

  Player(const Player& from);

  inline Player& operator=(const Player& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Player(Player&& from) noexcept
    : Player() {
    *this = ::std::move(from);
  }

  inline Player& operator=(Player&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const Player& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Player* internal_default_instance() {
    return reinterpret_cast<const Player*>(
               &_Player_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    4;

  void Swap(Player* other);
  friend void swap(Player& a, Player& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Player* New() const final {
    return CreateMaybeMessage<Player>(NULL);
  }

  Player* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<Player>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const Player& from);
  void MergeFrom(const Player& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Player* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // .moba.Vector3 position = 2;
  bool has_position() const;
  void clear_position();
  static const int kPositionFieldNumber = 2;
  private:
  const ::moba::Vector3& _internal_position() const;
  public:
  const ::moba::Vector3& position() const;
  ::moba::Vector3* release_position();
  ::moba::Vector3* mutable_position();
  void set_allocated_position(::moba::Vector3* position);

  // uint32 id = 1;
  void clear_id();
  static const int kIdFieldNumber = 1;
  ::google::protobuf::uint32 id() const;
  void set_id(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:moba.Player)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::moba::Vector3* position_;
  ::google::protobuf::uint32 id_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::protobuf_game_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// PlayerInput

// uint32 player_id = 1;
inline void PlayerInput::clear_player_id() {
  player_id_ = 0u;
}
inline ::google::protobuf::uint32 PlayerInput::player_id() const {
  // @@protoc_insertion_point(field_get:moba.PlayerInput.player_id)
  return player_id_;
}
inline void PlayerInput::set_player_id(::google::protobuf::uint32 value) {
  
  player_id_ = value;
  // @@protoc_insertion_point(field_set:moba.PlayerInput.player_id)
}

// uint32 frame_num = 2;
inline void PlayerInput::clear_frame_num() {
  frame_num_ = 0u;
}
inline ::google::protobuf::uint32 PlayerInput::frame_num() const {
  // @@protoc_insertion_point(field_get:moba.PlayerInput.frame_num)
  return frame_num_;
}
inline void PlayerInput::set_frame_num(::google::protobuf::uint32 value) {
  
  frame_num_ = value;
  // @@protoc_insertion_point(field_set:moba.PlayerInput.frame_num)
}

// .moba.Vector3 move_dir = 3;
inline bool PlayerInput::has_move_dir() const {
  return this != internal_default_instance() && move_dir_ != NULL;
}
inline void PlayerInput::clear_move_dir() {
  if (GetArenaNoVirtual() == NULL && move_dir_ != NULL) {
    delete move_dir_;
  }
  move_dir_ = NULL;
}
inline const ::moba::Vector3& PlayerInput::_internal_move_dir() const {
  return *move_dir_;
}
inline const ::moba::Vector3& PlayerInput::move_dir() const {
  const ::moba::Vector3* p = move_dir_;
  // @@protoc_insertion_point(field_get:moba.PlayerInput.move_dir)
  return p != NULL ? *p : *reinterpret_cast<const ::moba::Vector3*>(
      &::moba::_Vector3_default_instance_);
}
inline ::moba::Vector3* PlayerInput::release_move_dir() {
  // @@protoc_insertion_point(field_release:moba.PlayerInput.move_dir)
  
  ::moba::Vector3* temp = move_dir_;
  move_dir_ = NULL;
  return temp;
}
inline ::moba::Vector3* PlayerInput::mutable_move_dir() {
  
  if (move_dir_ == NULL) {
    auto* p = CreateMaybeMessage<::moba::Vector3>(GetArenaNoVirtual());
    move_dir_ = p;
  }
  // @@protoc_insertion_point(field_mutable:moba.PlayerInput.move_dir)
  return move_dir_;
}
inline void PlayerInput::set_allocated_move_dir(::moba::Vector3* move_dir) {
  ::google::protobuf::Arena* message_arena = GetArenaNoVirtual();
  if (message_arena == NULL) {
    delete move_dir_;
  }
  if (move_dir) {
    ::google::protobuf::Arena* submessage_arena = NULL;
    if (message_arena != submessage_arena) {
      move_dir = ::google::protobuf::internal::GetOwnedMessage(
          message_arena, move_dir, submessage_arena);
    }
    
  } else {
    
  }
  move_dir_ = move_dir;
  // @@protoc_insertion_point(field_set_allocated:moba.PlayerInput.move_dir)
}

// repeated uint32 skills = 4;
inline int PlayerInput::skills_size() const {
  return skills_.size();
}
inline void PlayerInput::clear_skills() {
  skills_.Clear();
}
inline ::google::protobuf::uint32 PlayerInput::skills(int index) const {
  // @@protoc_insertion_point(field_get:moba.PlayerInput.skills)
  return skills_.Get(index);
}
inline void PlayerInput::set_skills(int index, ::google::protobuf::uint32 value) {
  skills_.Set(index, value);
  // @@protoc_insertion_point(field_set:moba.PlayerInput.skills)
}
inline void PlayerInput::add_skills(::google::protobuf::uint32 value) {
  skills_.Add(value);
  // @@protoc_insertion_point(field_add:moba.PlayerInput.skills)
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
PlayerInput::skills() const {
  // @@protoc_insertion_point(field_list:moba.PlayerInput.skills)
  return skills_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
PlayerInput::mutable_skills() {
  // @@protoc_insertion_point(field_mutable_list:moba.PlayerInput.skills)
  return &skills_;
}

// -------------------------------------------------------------------

// Vector3

// float x = 1;
inline void Vector3::clear_x() {
  x_ = 0;
}
inline float Vector3::x() const {
  // @@protoc_insertion_point(field_get:moba.Vector3.x)
  return x_;
}
inline void Vector3::set_x(float value) {
  
  x_ = value;
  // @@protoc_insertion_point(field_set:moba.Vector3.x)
}

// float y = 2;
inline void Vector3::clear_y() {
  y_ = 0;
}
inline float Vector3::y() const {
  // @@protoc_insertion_point(field_get:moba.Vector3.y)
  return y_;
}
inline void Vector3::set_y(float value) {
  
  y_ = value;
  // @@protoc_insertion_point(field_set:moba.Vector3.y)
}

// float z = 3;
inline void Vector3::clear_z() {
  z_ = 0;
}
inline float Vector3::z() const {
  // @@protoc_insertion_point(field_get:moba.Vector3.z)
  return z_;
}
inline void Vector3::set_z(float value) {
  
  z_ = value;
  // @@protoc_insertion_point(field_set:moba.Vector3.z)
}

// -------------------------------------------------------------------

// FrameData

// uint32 frame_num = 1;
inline void FrameData::clear_frame_num() {
  frame_num_ = 0u;
}
inline ::google::protobuf::uint32 FrameData::frame_num() const {
  // @@protoc_insertion_point(field_get:moba.FrameData.frame_num)
  return frame_num_;
}
inline void FrameData::set_frame_num(::google::protobuf::uint32 value) {
  
  frame_num_ = value;
  // @@protoc_insertion_point(field_set:moba.FrameData.frame_num)
}

// repeated .moba.PlayerInput inputs = 2;
inline int FrameData::inputs_size() const {
  return inputs_.size();
}
inline void FrameData::clear_inputs() {
  inputs_.Clear();
}
inline ::moba::PlayerInput* FrameData::mutable_inputs(int index) {
  // @@protoc_insertion_point(field_mutable:moba.FrameData.inputs)
  return inputs_.Mutable(index);
}
inline ::google::protobuf::RepeatedPtrField< ::moba::PlayerInput >*
FrameData::mutable_inputs() {
  // @@protoc_insertion_point(field_mutable_list:moba.FrameData.inputs)
  return &inputs_;
}
inline const ::moba::PlayerInput& FrameData::inputs(int index) const {
  // @@protoc_insertion_point(field_get:moba.FrameData.inputs)
  return inputs_.Get(index);
}
inline ::moba::PlayerInput* FrameData::add_inputs() {
  // @@protoc_insertion_point(field_add:moba.FrameData.inputs)
  return inputs_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::moba::PlayerInput >&
FrameData::inputs() const {
  // @@protoc_insertion_point(field_list:moba.FrameData.inputs)
  return inputs_;
}

// -------------------------------------------------------------------

// GameState

// repeated .moba.Player players = 1;
inline int GameState::players_size() const {
  return players_.size();
}
inline void GameState::clear_players() {
  players_.Clear();
}
inline ::moba::Player* GameState::mutable_players(int index) {
  // @@protoc_insertion_point(field_mutable:moba.GameState.players)
  return players_.Mutable(index);
}
inline ::google::protobuf::RepeatedPtrField< ::moba::Player >*
GameState::mutable_players() {
  // @@protoc_insertion_point(field_mutable_list:moba.GameState.players)
  return &players_;
}
inline const ::moba::Player& GameState::players(int index) const {
  // @@protoc_insertion_point(field_get:moba.GameState.players)
  return players_.Get(index);
}
inline ::moba::Player* GameState::add_players() {
  // @@protoc_insertion_point(field_add:moba.GameState.players)
  return players_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::moba::Player >&
GameState::players() const {
  // @@protoc_insertion_point(field_list:moba.GameState.players)
  return players_;
}

// uint32 current_frame = 2;
inline void GameState::clear_current_frame() {
  current_frame_ = 0u;
}
inline ::google::protobuf::uint32 GameState::current_frame() const {
  // @@protoc_insertion_point(field_get:moba.GameState.current_frame)
  return current_frame_;
}
inline void GameState::set_current_frame(::google::protobuf::uint32 value) {
  
  current_frame_ = value;
  // @@protoc_insertion_point(field_set:moba.GameState.current_frame)
}

// -------------------------------------------------------------------

// Player

// uint32 id = 1;
inline void Player::clear_id() {
  id_ = 0u;
}
inline ::google::protobuf::uint32 Player::id() const {
  // @@protoc_insertion_point(field_get:moba.Player.id)
  return id_;
}
inline void Player::set_id(::google::protobuf::uint32 value) {
  
  id_ = value;
  // @@protoc_insertion_point(field_set:moba.Player.id)
}

// .moba.Vector3 position = 2;
inline bool Player::has_position() const {
  return this != internal_default_instance() && position_ != NULL;
}
inline void Player::clear_position() {
  if (GetArenaNoVirtual() == NULL && position_ != NULL) {
    delete position_;
  }
  position_ = NULL;
}
inline const ::moba::Vector3& Player::_internal_position() const {
  return *position_;
}
inline const ::moba::Vector3& Player::position() const {
  const ::moba::Vector3* p = position_;
  // @@protoc_insertion_point(field_get:moba.Player.position)
  return p != NULL ? *p : *reinterpret_cast<const ::moba::Vector3*>(
      &::moba::_Vector3_default_instance_);
}
inline ::moba::Vector3* Player::release_position() {
  // @@protoc_insertion_point(field_release:moba.Player.position)
  
  ::moba::Vector3* temp = position_;
  position_ = NULL;
  return temp;
}
inline ::moba::Vector3* Player::mutable_position() {
  
  if (position_ == NULL) {
    auto* p = CreateMaybeMessage<::moba::Vector3>(GetArenaNoVirtual());
    position_ = p;
  }
  // @@protoc_insertion_point(field_mutable:moba.Player.position)
  return position_;
}
inline void Player::set_allocated_position(::moba::Vector3* position) {
  ::google::protobuf::Arena* message_arena = GetArenaNoVirtual();
  if (message_arena == NULL) {
    delete position_;
  }
  if (position) {
    ::google::protobuf::Arena* submessage_arena = NULL;
    if (message_arena != submessage_arena) {
      position = ::google::protobuf::internal::GetOwnedMessage(
          message_arena, position, submessage_arena);
    }
    
  } else {
    
  }
  position_ = position;
  // @@protoc_insertion_point(field_set_allocated:moba.Player.position)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------

// -------------------------------------------------------------------

// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace moba

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_INCLUDED_game_2eproto
