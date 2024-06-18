#pragma once

#include "Vitrae/Util/Hashing.hpp"
#include "Vitrae/Util/StringId.hpp"
#include "Vitrae/Util/Variant.hpp"

#include "dynasma/util/dynamic_typing.hpp"

#include <map>
#include <span>
#include <vector>

namespace Vitrae
{

struct PropertySpec
{
    std::string name;
    const TypeInfo &typeInfo;
};

class PropertyList : public dynasma::PolymorphicBase
{
    friend struct std::hash<PropertyList>;

    std::map<StringId, PropertySpec> m_mappedSpecs;
    std::vector<StringId> m_specNameIds;
    std::vector<PropertySpec> m_specList;

    std::size_t m_hash;

  public:
    inline PropertyList() : m_hash(0) {}
    PropertyList(PropertyList const &) = default;
    PropertyList(PropertyList &&) = default;

    template <class ContainerT>
    PropertyList(const ContainerT &specs)
        requires(std::ranges::range<ContainerT> &&
                 std::convertible_to<std::ranges::range_value_t<ContainerT>, const PropertySpec &>)
    {
        for (const auto &spec : specs) {
            m_mappedSpecs.emplace(spec.name, spec);
        }

        m_hash = 0;
        for (auto [nameId, spec] : m_mappedSpecs) {
            m_specNameIds.push_back(nameId);
            m_specList.push_back(spec);

            m_hash = combinedHashes<3>(
                {{m_hash, std::hash<StringId>{}(nameId), spec.typeInfo.p_id->hash_code()}});
        }
    }

    inline PropertyList(const std::map<StringId, PropertySpec> &mappedSpecs)
        : m_mappedSpecs(mappedSpecs)
    {
        m_hash = 0;
        for (auto [nameId, spec] : m_mappedSpecs) {
            m_specNameIds.push_back(nameId);
            m_specList.push_back(spec);

            m_hash = combinedHashes<3>(
                {{m_hash, std::hash<StringId>{}(nameId), spec.typeInfo.p_id->hash_code()}});
        }
    }

    inline PropertyList(std::map<StringId, PropertySpec> &&mappedSpecs)
        : m_mappedSpecs(std::move(mappedSpecs))
    {
        m_hash = 0;
        for (auto [nameId, spec] : m_mappedSpecs) {
            m_specNameIds.push_back(nameId);
            m_specList.push_back(spec);

            m_hash = combinedHashes<3>(
                {{m_hash, std::hash<StringId>{}(nameId), spec.typeInfo.p_id->hash_code()}});
        }
    }

    virtual ~PropertyList() = default;

    PropertyList &operator=(PropertyList const &) = default;
    PropertyList &operator=(PropertyList &&) = default;

    /*
    Getters
    */

    inline const std::map<StringId, PropertySpec> &getMappedSpecs() const { return m_mappedSpecs; }

    inline std::span<const StringId> getSpecNameIds() const { return m_specNameIds; }

    inline std::span<const PropertySpec> getSpecList() const { return m_specList; }

    inline std::size_t getHash() const { return m_hash; }

    /*
    Comparisons
    */

    bool operator==(const PropertyList &other) const { return m_hash == other.m_hash; }
    bool operator!=(const PropertyList &other) const { return m_hash != other.m_hash; }
    bool operator<(const PropertyList &other) const { return m_hash < other.m_hash; }
    bool operator<=(const PropertyList &other) const { return m_hash <= other.m_hash; }
    bool operator>(const PropertyList &other) const { return m_hash > other.m_hash; }
    bool operator>=(const PropertyList &other) const { return m_hash >= other.m_hash; }
};

} // namespace Vitrae

namespace std
{

template <> struct hash<Vitrae::PropertyList>
{
    std::size_t operator()(const Vitrae::PropertyList &pl) const { return pl.m_hash; }
};
} // namespace std