// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_ZKINTERFACE_ZKINTERFACE_H_
#define FLATBUFFERS_GENERATED_ZKINTERFACE_ZKINTERFACE_H_

#include "flatbuffers/flatbuffers.h"

namespace zkinterface {

struct GadgetCall;

struct GadgetReturn;

struct Connection;

struct KeyValue;

struct R1CSConstraints;

struct BilinearConstraint;

struct AssignedVariables;

struct VariableValues;

struct Root;

/// The messages that the caller and gadget can exchange.
enum Message {
  Message_NONE = 0,
  Message_GadgetCall = 1,
  Message_GadgetReturn = 2,
  Message_R1CSConstraints = 3,
  Message_AssignedVariables = 4,
  Message_Connection = 5,
  Message_MIN = Message_NONE,
  Message_MAX = Message_Connection
};

inline const Message (&EnumValuesMessage())[6] {
  static const Message values[] = {
    Message_NONE,
    Message_GadgetCall,
    Message_GadgetReturn,
    Message_R1CSConstraints,
    Message_AssignedVariables,
    Message_Connection
  };
  return values;
}

inline const char * const *EnumNamesMessage() {
  static const char * const names[] = {
    "NONE",
    "GadgetCall",
    "GadgetReturn",
    "R1CSConstraints",
    "AssignedVariables",
    "Connection",
    nullptr
  };
  return names;
}

inline const char *EnumNameMessage(Message e) {
  if (e < Message_NONE || e > Message_Connection) return "";
  const size_t index = static_cast<int>(e);
  return EnumNamesMessage()[index];
}

template<typename T> struct MessageTraits {
  static const Message enum_value = Message_NONE;
};

template<> struct MessageTraits<GadgetCall> {
  static const Message enum_value = Message_GadgetCall;
};

template<> struct MessageTraits<GadgetReturn> {
  static const Message enum_value = Message_GadgetReturn;
};

template<> struct MessageTraits<R1CSConstraints> {
  static const Message enum_value = Message_R1CSConstraints;
};

template<> struct MessageTraits<AssignedVariables> {
  static const Message enum_value = Message_AssignedVariables;
};

template<> struct MessageTraits<Connection> {
  static const Message enum_value = Message_Connection;
};

bool VerifyMessage(flatbuffers::Verifier &verifier, const void *obj, Message type);
bool VerifyMessageVector(flatbuffers::Verifier &verifier, const flatbuffers::Vector<flatbuffers::Offset<void>> *values, const flatbuffers::Vector<uint8_t> *types);

/// Caller calls a gadget.
struct GadgetCall FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_INPUTS = 4,
    VT_GENERATE_R1CS = 6,
    VT_GENERATE_ASSIGNMENT = 8,
    VT_FIELD_ORDER = 10,
    VT_CONFIGURATION = 12
  };
  /// Incoming Variables to use as connections to the gadget.
  /// Allocated by the caller.
  /// Includes the first free Variable ID; the gadget can allocate new IDs
  /// starting with `inputs.free_variable_id`.
  /// The same structure must be provided for R1CS and assignment generation.
  const Connection *inputs() const {
    return GetPointer<const Connection *>(VT_INPUTS);
  }
  /// Whether constraints should be generated.
  bool generate_r1cs() const {
    return GetField<uint8_t>(VT_GENERATE_R1CS, 0) != 0;
  }
  /// Whether an assignment should be generated.
  /// Provide witness values to the gadget.
  bool generate_assignment() const {
    return GetField<uint8_t>(VT_GENERATE_ASSIGNMENT, 0) != 0;
  }
  /// The order of the field used by the current system.
  /// A BigInt.
  const flatbuffers::Vector<uint8_t> *field_order() const {
    return GetPointer<const flatbuffers::Vector<uint8_t> *>(VT_FIELD_ORDER);
  }
  /// Optional: Any static parameter that may influence the instance
  /// construction. Parameters can be standard, conventional, or custom.
  /// Example: function_name, if a gadget supports multiple function variants.
  /// Example: the depth of a Merkle tree.
  /// Counter-example: a Merkle path is not configuration (rather witness).
  const flatbuffers::Vector<flatbuffers::Offset<KeyValue>> *configuration() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<KeyValue>> *>(VT_CONFIGURATION);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_INPUTS) &&
           verifier.VerifyTable(inputs()) &&
           VerifyField<uint8_t>(verifier, VT_GENERATE_R1CS) &&
           VerifyField<uint8_t>(verifier, VT_GENERATE_ASSIGNMENT) &&
           VerifyOffset(verifier, VT_FIELD_ORDER) &&
           verifier.VerifyVector(field_order()) &&
           VerifyOffset(verifier, VT_CONFIGURATION) &&
           verifier.VerifyVector(configuration()) &&
           verifier.VerifyVectorOfTables(configuration()) &&
           verifier.EndTable();
  }
};

struct GadgetCallBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_inputs(flatbuffers::Offset<Connection> inputs) {
    fbb_.AddOffset(GadgetCall::VT_INPUTS, inputs);
  }
  void add_generate_r1cs(bool generate_r1cs) {
    fbb_.AddElement<uint8_t>(GadgetCall::VT_GENERATE_R1CS, static_cast<uint8_t>(generate_r1cs), 0);
  }
  void add_generate_assignment(bool generate_assignment) {
    fbb_.AddElement<uint8_t>(GadgetCall::VT_GENERATE_ASSIGNMENT, static_cast<uint8_t>(generate_assignment), 0);
  }
  void add_field_order(flatbuffers::Offset<flatbuffers::Vector<uint8_t>> field_order) {
    fbb_.AddOffset(GadgetCall::VT_FIELD_ORDER, field_order);
  }
  void add_configuration(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<KeyValue>>> configuration) {
    fbb_.AddOffset(GadgetCall::VT_CONFIGURATION, configuration);
  }
  explicit GadgetCallBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  GadgetCallBuilder &operator=(const GadgetCallBuilder &);
  flatbuffers::Offset<GadgetCall> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<GadgetCall>(end);
    return o;
  }
};

inline flatbuffers::Offset<GadgetCall> CreateGadgetCall(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<Connection> inputs = 0,
    bool generate_r1cs = false,
    bool generate_assignment = false,
    flatbuffers::Offset<flatbuffers::Vector<uint8_t>> field_order = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<KeyValue>>> configuration = 0) {
  GadgetCallBuilder builder_(_fbb);
  builder_.add_configuration(configuration);
  builder_.add_field_order(field_order);
  builder_.add_inputs(inputs);
  builder_.add_generate_assignment(generate_assignment);
  builder_.add_generate_r1cs(generate_r1cs);
  return builder_.Finish();
}

inline flatbuffers::Offset<GadgetCall> CreateGadgetCallDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<Connection> inputs = 0,
    bool generate_r1cs = false,
    bool generate_assignment = false,
    const std::vector<uint8_t> *field_order = nullptr,
    const std::vector<flatbuffers::Offset<KeyValue>> *configuration = nullptr) {
  auto field_order__ = field_order ? _fbb.CreateVector<uint8_t>(*field_order) : 0;
  auto configuration__ = configuration ? _fbb.CreateVector<flatbuffers::Offset<KeyValue>>(*configuration) : 0;
  return zkinterface::CreateGadgetCall(
      _fbb,
      inputs,
      generate_r1cs,
      generate_assignment,
      field_order__,
      configuration__);
}

/// The gadget returns to the caller. This is the final message
/// after all R1CSConstraints or AssignedVariables have been sent.
struct GadgetReturn FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_OUTPUTS = 4,
    VT_ERROR = 6
  };
  /// Outgoing Variables to use as connections to the gadget.
  /// There may be no Outgoing Variables if the gadget is a pure assertion.
  /// Allocated by the gadget.
  /// Include the first variable ID free after the gadget call;
  /// `outputs.free_variable_id` is greater than all IDs allocated by the gadget.
  const Connection *outputs() const {
    return GetPointer<const Connection *>(VT_OUTPUTS);
  }
  /// Optional: An error message. Null if no error.
  const flatbuffers::String *error() const {
    return GetPointer<const flatbuffers::String *>(VT_ERROR);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_OUTPUTS) &&
           verifier.VerifyTable(outputs()) &&
           VerifyOffset(verifier, VT_ERROR) &&
           verifier.VerifyString(error()) &&
           verifier.EndTable();
  }
};

struct GadgetReturnBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_outputs(flatbuffers::Offset<Connection> outputs) {
    fbb_.AddOffset(GadgetReturn::VT_OUTPUTS, outputs);
  }
  void add_error(flatbuffers::Offset<flatbuffers::String> error) {
    fbb_.AddOffset(GadgetReturn::VT_ERROR, error);
  }
  explicit GadgetReturnBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  GadgetReturnBuilder &operator=(const GadgetReturnBuilder &);
  flatbuffers::Offset<GadgetReturn> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<GadgetReturn>(end);
    return o;
  }
};

inline flatbuffers::Offset<GadgetReturn> CreateGadgetReturn(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<Connection> outputs = 0,
    flatbuffers::Offset<flatbuffers::String> error = 0) {
  GadgetReturnBuilder builder_(_fbb);
  builder_.add_error(error);
  builder_.add_outputs(outputs);
  return builder_.Finish();
}

inline flatbuffers::Offset<GadgetReturn> CreateGadgetReturnDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<Connection> outputs = 0,
    const char *error = nullptr) {
  auto error__ = error ? _fbb.CreateString(error) : 0;
  return zkinterface::CreateGadgetReturn(
      _fbb,
      outputs,
      error__);
}

/// A connection into a sub-circuits.
struct Connection FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_FREE_VARIABLE_ID = 4,
    VT_VARIABLE_IDS = 6,
    VT_VALUES = 8,
    VT_INFO = 10
  };
  /// First variable ID free after this connection.
  /// A variable ID greater than all IDs allocated at the time.
  uint64_t free_variable_id() const {
    return GetField<uint64_t>(VT_FREE_VARIABLE_ID, 0);
  }
  /// Variables to use as connections to the sub-circuit.
  const flatbuffers::Vector<uint64_t> *variable_ids() const {
    return GetPointer<const flatbuffers::Vector<uint64_t> *>(VT_VARIABLE_IDS);
  }
  /// Optional: The values assigned to variables, if any.
  /// Contiguous BigInts in the same order as `variable_ids`.
  const flatbuffers::Vector<uint8_t> *values() const {
    return GetPointer<const flatbuffers::Vector<uint8_t> *>(VT_VALUES);
  }
  /// Optional: Any info that may be useful to the recipient.
  /// Example: a Merkle authentication path.
  const flatbuffers::Vector<flatbuffers::Offset<KeyValue>> *info() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<KeyValue>> *>(VT_INFO);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint64_t>(verifier, VT_FREE_VARIABLE_ID) &&
           VerifyOffset(verifier, VT_VARIABLE_IDS) &&
           verifier.VerifyVector(variable_ids()) &&
           VerifyOffset(verifier, VT_VALUES) &&
           verifier.VerifyVector(values()) &&
           VerifyOffset(verifier, VT_INFO) &&
           verifier.VerifyVector(info()) &&
           verifier.VerifyVectorOfTables(info()) &&
           verifier.EndTable();
  }
};

struct ConnectionBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_free_variable_id(uint64_t free_variable_id) {
    fbb_.AddElement<uint64_t>(Connection::VT_FREE_VARIABLE_ID, free_variable_id, 0);
  }
  void add_variable_ids(flatbuffers::Offset<flatbuffers::Vector<uint64_t>> variable_ids) {
    fbb_.AddOffset(Connection::VT_VARIABLE_IDS, variable_ids);
  }
  void add_values(flatbuffers::Offset<flatbuffers::Vector<uint8_t>> values) {
    fbb_.AddOffset(Connection::VT_VALUES, values);
  }
  void add_info(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<KeyValue>>> info) {
    fbb_.AddOffset(Connection::VT_INFO, info);
  }
  explicit ConnectionBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ConnectionBuilder &operator=(const ConnectionBuilder &);
  flatbuffers::Offset<Connection> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<Connection>(end);
    return o;
  }
};

inline flatbuffers::Offset<Connection> CreateConnection(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint64_t free_variable_id = 0,
    flatbuffers::Offset<flatbuffers::Vector<uint64_t>> variable_ids = 0,
    flatbuffers::Offset<flatbuffers::Vector<uint8_t>> values = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<KeyValue>>> info = 0) {
  ConnectionBuilder builder_(_fbb);
  builder_.add_free_variable_id(free_variable_id);
  builder_.add_info(info);
  builder_.add_values(values);
  builder_.add_variable_ids(variable_ids);
  return builder_.Finish();
}

inline flatbuffers::Offset<Connection> CreateConnectionDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint64_t free_variable_id = 0,
    const std::vector<uint64_t> *variable_ids = nullptr,
    const std::vector<uint8_t> *values = nullptr,
    const std::vector<flatbuffers::Offset<KeyValue>> *info = nullptr) {
  auto variable_ids__ = variable_ids ? _fbb.CreateVector<uint64_t>(*variable_ids) : 0;
  auto values__ = values ? _fbb.CreateVector<uint8_t>(*values) : 0;
  auto info__ = info ? _fbb.CreateVector<flatbuffers::Offset<KeyValue>>(*info) : 0;
  return zkinterface::CreateConnection(
      _fbb,
      free_variable_id,
      variable_ids__,
      values__,
      info__);
}

/// Generic key-value for custom attributes.
struct KeyValue FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_KEY = 4,
    VT_VALUE = 6
  };
  const flatbuffers::String *key() const {
    return GetPointer<const flatbuffers::String *>(VT_KEY);
  }
  const flatbuffers::Vector<uint8_t> *value() const {
    return GetPointer<const flatbuffers::Vector<uint8_t> *>(VT_VALUE);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_KEY) &&
           verifier.VerifyString(key()) &&
           VerifyOffset(verifier, VT_VALUE) &&
           verifier.VerifyVector(value()) &&
           verifier.EndTable();
  }
};

struct KeyValueBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_key(flatbuffers::Offset<flatbuffers::String> key) {
    fbb_.AddOffset(KeyValue::VT_KEY, key);
  }
  void add_value(flatbuffers::Offset<flatbuffers::Vector<uint8_t>> value) {
    fbb_.AddOffset(KeyValue::VT_VALUE, value);
  }
  explicit KeyValueBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  KeyValueBuilder &operator=(const KeyValueBuilder &);
  flatbuffers::Offset<KeyValue> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<KeyValue>(end);
    return o;
  }
};

inline flatbuffers::Offset<KeyValue> CreateKeyValue(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> key = 0,
    flatbuffers::Offset<flatbuffers::Vector<uint8_t>> value = 0) {
  KeyValueBuilder builder_(_fbb);
  builder_.add_value(value);
  builder_.add_key(key);
  return builder_.Finish();
}

inline flatbuffers::Offset<KeyValue> CreateKeyValueDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *key = nullptr,
    const std::vector<uint8_t> *value = nullptr) {
  auto key__ = key ? _fbb.CreateString(key) : 0;
  auto value__ = value ? _fbb.CreateVector<uint8_t>(*value) : 0;
  return zkinterface::CreateKeyValue(
      _fbb,
      key__,
      value__);
}

/// Report constraints to be added to the constraints system.
/// To send to the stream of constraints.
struct R1CSConstraints FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_CONSTRAINTS = 4
  };
  const flatbuffers::Vector<flatbuffers::Offset<BilinearConstraint>> *constraints() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<BilinearConstraint>> *>(VT_CONSTRAINTS);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_CONSTRAINTS) &&
           verifier.VerifyVector(constraints()) &&
           verifier.VerifyVectorOfTables(constraints()) &&
           verifier.EndTable();
  }
};

struct R1CSConstraintsBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_constraints(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<BilinearConstraint>>> constraints) {
    fbb_.AddOffset(R1CSConstraints::VT_CONSTRAINTS, constraints);
  }
  explicit R1CSConstraintsBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  R1CSConstraintsBuilder &operator=(const R1CSConstraintsBuilder &);
  flatbuffers::Offset<R1CSConstraints> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<R1CSConstraints>(end);
    return o;
  }
};

inline flatbuffers::Offset<R1CSConstraints> CreateR1CSConstraints(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<BilinearConstraint>>> constraints = 0) {
  R1CSConstraintsBuilder builder_(_fbb);
  builder_.add_constraints(constraints);
  return builder_.Finish();
}

inline flatbuffers::Offset<R1CSConstraints> CreateR1CSConstraintsDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const std::vector<flatbuffers::Offset<BilinearConstraint>> *constraints = nullptr) {
  auto constraints__ = constraints ? _fbb.CreateVector<flatbuffers::Offset<BilinearConstraint>>(*constraints) : 0;
  return zkinterface::CreateR1CSConstraints(
      _fbb,
      constraints__);
}

/// An R1CS constraint between variables.
struct BilinearConstraint FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_LINEAR_COMBINATION_A = 4,
    VT_LINEAR_COMBINATION_B = 6,
    VT_LINEAR_COMBINATION_C = 8
  };
  const VariableValues *linear_combination_a() const {
    return GetPointer<const VariableValues *>(VT_LINEAR_COMBINATION_A);
  }
  const VariableValues *linear_combination_b() const {
    return GetPointer<const VariableValues *>(VT_LINEAR_COMBINATION_B);
  }
  const VariableValues *linear_combination_c() const {
    return GetPointer<const VariableValues *>(VT_LINEAR_COMBINATION_C);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_LINEAR_COMBINATION_A) &&
           verifier.VerifyTable(linear_combination_a()) &&
           VerifyOffset(verifier, VT_LINEAR_COMBINATION_B) &&
           verifier.VerifyTable(linear_combination_b()) &&
           VerifyOffset(verifier, VT_LINEAR_COMBINATION_C) &&
           verifier.VerifyTable(linear_combination_c()) &&
           verifier.EndTable();
  }
};

struct BilinearConstraintBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_linear_combination_a(flatbuffers::Offset<VariableValues> linear_combination_a) {
    fbb_.AddOffset(BilinearConstraint::VT_LINEAR_COMBINATION_A, linear_combination_a);
  }
  void add_linear_combination_b(flatbuffers::Offset<VariableValues> linear_combination_b) {
    fbb_.AddOffset(BilinearConstraint::VT_LINEAR_COMBINATION_B, linear_combination_b);
  }
  void add_linear_combination_c(flatbuffers::Offset<VariableValues> linear_combination_c) {
    fbb_.AddOffset(BilinearConstraint::VT_LINEAR_COMBINATION_C, linear_combination_c);
  }
  explicit BilinearConstraintBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  BilinearConstraintBuilder &operator=(const BilinearConstraintBuilder &);
  flatbuffers::Offset<BilinearConstraint> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<BilinearConstraint>(end);
    return o;
  }
};

inline flatbuffers::Offset<BilinearConstraint> CreateBilinearConstraint(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<VariableValues> linear_combination_a = 0,
    flatbuffers::Offset<VariableValues> linear_combination_b = 0,
    flatbuffers::Offset<VariableValues> linear_combination_c = 0) {
  BilinearConstraintBuilder builder_(_fbb);
  builder_.add_linear_combination_c(linear_combination_c);
  builder_.add_linear_combination_b(linear_combination_b);
  builder_.add_linear_combination_a(linear_combination_a);
  return builder_.Finish();
}

/// Report local assignments computed by the gadget.
/// To send to the stream of assigned variables.
/// Does not include input and output variables.
struct AssignedVariables FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_VALUES = 4
  };
  const VariableValues *values() const {
    return GetPointer<const VariableValues *>(VT_VALUES);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_VALUES) &&
           verifier.VerifyTable(values()) &&
           verifier.EndTable();
  }
};

struct AssignedVariablesBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_values(flatbuffers::Offset<VariableValues> values) {
    fbb_.AddOffset(AssignedVariables::VT_VALUES, values);
  }
  explicit AssignedVariablesBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  AssignedVariablesBuilder &operator=(const AssignedVariablesBuilder &);
  flatbuffers::Offset<AssignedVariables> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<AssignedVariables>(end);
    return o;
  }
};

inline flatbuffers::Offset<AssignedVariables> CreateAssignedVariables(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<VariableValues> values = 0) {
  AssignedVariablesBuilder builder_(_fbb);
  builder_.add_values(values);
  return builder_.Finish();
}

/// Concrete variable values.
/// Used for linear combinations and assignments.
struct VariableValues FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_VARIABLE_IDS = 4,
    VT_VALUES = 6
  };
  /// The IDs of the variables being assigned to.
  const flatbuffers::Vector<uint64_t> *variable_ids() const {
    return GetPointer<const flatbuffers::Vector<uint64_t> *>(VT_VARIABLE_IDS);
  }
  /// Field Elements assigned to variables.
  /// Contiguous BigInts in the same order as variable_ids.
  ///
  /// The field in use is defined in `instance.field_order`.
  ///
  /// The size of an element representation is determined by:
  ///     element size = elements.length / variable_ids.length
  ///
  /// The element representation may be truncated and therefore shorter
  /// than the canonical representation. Truncated bytes are treated as zeros.
  const flatbuffers::Vector<uint8_t> *values() const {
    return GetPointer<const flatbuffers::Vector<uint8_t> *>(VT_VALUES);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_VARIABLE_IDS) &&
           verifier.VerifyVector(variable_ids()) &&
           VerifyOffset(verifier, VT_VALUES) &&
           verifier.VerifyVector(values()) &&
           verifier.EndTable();
  }
};

struct VariableValuesBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_variable_ids(flatbuffers::Offset<flatbuffers::Vector<uint64_t>> variable_ids) {
    fbb_.AddOffset(VariableValues::VT_VARIABLE_IDS, variable_ids);
  }
  void add_values(flatbuffers::Offset<flatbuffers::Vector<uint8_t>> values) {
    fbb_.AddOffset(VariableValues::VT_VALUES, values);
  }
  explicit VariableValuesBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  VariableValuesBuilder &operator=(const VariableValuesBuilder &);
  flatbuffers::Offset<VariableValues> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<VariableValues>(end);
    return o;
  }
};

inline flatbuffers::Offset<VariableValues> CreateVariableValues(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::Vector<uint64_t>> variable_ids = 0,
    flatbuffers::Offset<flatbuffers::Vector<uint8_t>> values = 0) {
  VariableValuesBuilder builder_(_fbb);
  builder_.add_values(values);
  builder_.add_variable_ids(variable_ids);
  return builder_.Finish();
}

inline flatbuffers::Offset<VariableValues> CreateVariableValuesDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const std::vector<uint64_t> *variable_ids = nullptr,
    const std::vector<uint8_t> *values = nullptr) {
  auto variable_ids__ = variable_ids ? _fbb.CreateVector<uint64_t>(*variable_ids) : 0;
  auto values__ = values ? _fbb.CreateVector<uint8_t>(*values) : 0;
  return zkinterface::CreateVariableValues(
      _fbb,
      variable_ids__,
      values__);
}

struct Root FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_MESSAGE_TYPE = 4,
    VT_MESSAGE = 6
  };
  Message message_type() const {
    return static_cast<Message>(GetField<uint8_t>(VT_MESSAGE_TYPE, 0));
  }
  const void *message() const {
    return GetPointer<const void *>(VT_MESSAGE);
  }
  template<typename T> const T *message_as() const;
  const GadgetCall *message_as_GadgetCall() const {
    return message_type() == Message_GadgetCall ? static_cast<const GadgetCall *>(message()) : nullptr;
  }
  const GadgetReturn *message_as_GadgetReturn() const {
    return message_type() == Message_GadgetReturn ? static_cast<const GadgetReturn *>(message()) : nullptr;
  }
  const R1CSConstraints *message_as_R1CSConstraints() const {
    return message_type() == Message_R1CSConstraints ? static_cast<const R1CSConstraints *>(message()) : nullptr;
  }
  const AssignedVariables *message_as_AssignedVariables() const {
    return message_type() == Message_AssignedVariables ? static_cast<const AssignedVariables *>(message()) : nullptr;
  }
  const Connection *message_as_Connection() const {
    return message_type() == Message_Connection ? static_cast<const Connection *>(message()) : nullptr;
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint8_t>(verifier, VT_MESSAGE_TYPE) &&
           VerifyOffset(verifier, VT_MESSAGE) &&
           VerifyMessage(verifier, message(), message_type()) &&
           verifier.EndTable();
  }
};

template<> inline const GadgetCall *Root::message_as<GadgetCall>() const {
  return message_as_GadgetCall();
}

template<> inline const GadgetReturn *Root::message_as<GadgetReturn>() const {
  return message_as_GadgetReturn();
}

template<> inline const R1CSConstraints *Root::message_as<R1CSConstraints>() const {
  return message_as_R1CSConstraints();
}

template<> inline const AssignedVariables *Root::message_as<AssignedVariables>() const {
  return message_as_AssignedVariables();
}

template<> inline const Connection *Root::message_as<Connection>() const {
  return message_as_Connection();
}

struct RootBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_message_type(Message message_type) {
    fbb_.AddElement<uint8_t>(Root::VT_MESSAGE_TYPE, static_cast<uint8_t>(message_type), 0);
  }
  void add_message(flatbuffers::Offset<void> message) {
    fbb_.AddOffset(Root::VT_MESSAGE, message);
  }
  explicit RootBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  RootBuilder &operator=(const RootBuilder &);
  flatbuffers::Offset<Root> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<Root>(end);
    return o;
  }
};

inline flatbuffers::Offset<Root> CreateRoot(
    flatbuffers::FlatBufferBuilder &_fbb,
    Message message_type = Message_NONE,
    flatbuffers::Offset<void> message = 0) {
  RootBuilder builder_(_fbb);
  builder_.add_message(message);
  builder_.add_message_type(message_type);
  return builder_.Finish();
}

inline bool VerifyMessage(flatbuffers::Verifier &verifier, const void *obj, Message type) {
  switch (type) {
    case Message_NONE: {
      return true;
    }
    case Message_GadgetCall: {
      auto ptr = reinterpret_cast<const GadgetCall *>(obj);
      return verifier.VerifyTable(ptr);
    }
    case Message_GadgetReturn: {
      auto ptr = reinterpret_cast<const GadgetReturn *>(obj);
      return verifier.VerifyTable(ptr);
    }
    case Message_R1CSConstraints: {
      auto ptr = reinterpret_cast<const R1CSConstraints *>(obj);
      return verifier.VerifyTable(ptr);
    }
    case Message_AssignedVariables: {
      auto ptr = reinterpret_cast<const AssignedVariables *>(obj);
      return verifier.VerifyTable(ptr);
    }
    case Message_Connection: {
      auto ptr = reinterpret_cast<const Connection *>(obj);
      return verifier.VerifyTable(ptr);
    }
    default: return false;
  }
}

inline bool VerifyMessageVector(flatbuffers::Verifier &verifier, const flatbuffers::Vector<flatbuffers::Offset<void>> *values, const flatbuffers::Vector<uint8_t> *types) {
  if (!values || !types) return !values && !types;
  if (values->size() != types->size()) return false;
  for (flatbuffers::uoffset_t i = 0; i < values->size(); ++i) {
    if (!VerifyMessage(
        verifier,  values->Get(i), types->GetEnum<Message>(i))) {
      return false;
    }
  }
  return true;
}

inline const zkinterface::Root *GetRoot(const void *buf) {
  return flatbuffers::GetRoot<zkinterface::Root>(buf);
}

inline const zkinterface::Root *GetSizePrefixedRoot(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<zkinterface::Root>(buf);
}

inline const char *RootIdentifier() {
  return "zkif";
}

inline bool RootBufferHasIdentifier(const void *buf) {
  return flatbuffers::BufferHasIdentifier(
      buf, RootIdentifier());
}

inline bool VerifyRootBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<zkinterface::Root>(RootIdentifier());
}

inline bool VerifySizePrefixedRootBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<zkinterface::Root>(RootIdentifier());
}

inline const char *RootExtension() {
  return "zkif";
}

inline void FinishRootBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<zkinterface::Root> root) {
  fbb.Finish(root, RootIdentifier());
}

inline void FinishSizePrefixedRootBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<zkinterface::Root> root) {
  fbb.FinishSizePrefixed(root, RootIdentifier());
}

}  // namespace zkinterface

#endif  // FLATBUFFERS_GENERATED_ZKINTERFACE_ZKINTERFACE_H_
