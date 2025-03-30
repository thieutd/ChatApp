#pragma once
#include "Helper.inl"

template <typename... Types> std::tuple<Types...> &operator<<(std::tuple<Types...> &tuple, const drogon::orm::Row &row)
{
    size_t offset = 0;
    (..., (std::get<Types>(tuple) = Types(row, offset), offset += Types::getColumnNumber()));
    return tuple;
}

namespace server::models
{
const std::vector<std::string> kUserFields{std::begin(internal::kUserFieldsArray), std::end(internal::kUserFieldsArray)};
const std::vector<std::string> kUserRegistrationFields{std::begin(internal::kUserRegistrationFieldsArray), std::end(internal::kUserRegistrationFieldsArray)};
const std::vector<std::string> kUserInfoFields{std::begin(internal::kUserInfoFieldsArray), std::end(internal::kUserInfoFieldsArray)};
const std::vector<std::string> kUserRedisInfoFields{std::begin(internal::kUserRedisInfoFieldsArray), std::end(internal::kUserRedisInfoFieldsArray)};
const std::vector<std::string> kUserUpdateFields{std::begin(internal::kUserUpdateFieldsArray),
                                                      std::end(internal::kUserUpdateFieldsArray)};
const std::vector<std::string> kUserCreationByAdminFields{std::begin(internal::kUserCreationByAdminArray), std::end(internal::kUserCreationByAdminArray)};
const std::vector<std::string> kUserUpdateByAdminFields{std::begin(internal::kUserUpdateByAdminFieldsArray),
                                                        std::end(internal::kUserUpdateByAdminFieldsArray)};

const std::vector<std::string> kCommonRoomsViewFields{std::begin(internal::kCommonRoomsViewFieldsArray), std::end(internal::kCommonRoomsViewFieldsArray)};
const std::vector<std::string> kCommonRoomsViewResultFields{std::begin(internal::kCommonRoomsViewResultFieldsArray), std::end(internal::kCommonRoomsViewResultFieldsArray)};
} // namespace server::models