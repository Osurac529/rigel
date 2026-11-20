#include "rigel/mesh/vertex.hpp"

namespace rigel::mesh {

namespace {

class HashVisitor {
public:
  void operator()(const math::vec2f &attribute) { hash_ = vec2_hasher_(attribute); }

  void operator()(const math::vec3f &attribute) { hash_ = vec3_hasher_(attribute); }

  void operator()(const math::vec4f &attribute) { hash_ = vec4_hasher_(attribute); }

  std::size_t hash() const { return hash_; }

private:
  std::size_t hash_;
  std::hash<math::vec2f> vec2_hasher_;
  std::hash<math::vec3f> vec3_hasher_;
  std::hash<math::vec4f> vec4_hasher_;
};

} // namespace

void Vertex::Set(const AttributeID attribute_id, const math::vec2f &attribute) {
  attributes_[attribute_id] = attribute;
}

void Vertex::Set(const AttributeID attribute_id, const math::vec3f &attribute) {
  attributes_[attribute_id] = attribute;
}

void Vertex::Set(const AttributeID attribute_id, const math::vec4f &attribute) {
  attributes_[attribute_id] = attribute;
}

std::vector<AttributeID> Vertex::GetAttributeIDs() const {
  std::vector<AttributeID> attribute_ids;
  attribute_ids.reserve(attributes_.size());

  for (const auto &[attribute_id, ignore] : attributes_) {
    attribute_ids.push_back(attribute_id);
  }

  return attribute_ids;
}

std::size_t Vertex::hash() const {
  if (0 == hash_) {
    hash_ = 17;

    HashVisitor hash_visitor;

    for (const auto &[ignore, attribute] : attributes_) {
      std::visit(hash_visitor, attribute);
      hash_ = hash_ * 31 + hash_visitor.hash();
    }
  }

  return hash_;
}

const std::unordered_map<AttributeID, Attribute> &Vertex::attributes() const {
  return attributes_;
}

bool Vertex::operator==(const Vertex &other) const {
  // do not include the hash
  return attributes_ == other.attributes_;
}

} // namespace rigel::mesh
