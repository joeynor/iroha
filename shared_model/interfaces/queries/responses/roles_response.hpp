/**
 * Copyright Soramitsu Co., Ltd. 2017 All Rights Reserved.
 * http://soramitsu.co.jp
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef IROHA_SHARED_MODEL_ROLES_RESPONSE_HPP
#define IROHA_SHARED_MODEL_ROLES_RESPONSE_HPP

#include <boost/algorithm/string/join.hpp>
#include "interfaces/common_objects/types.hpp"
#include "interfaces/hashable.hpp"
#include "model/queries/responses/roles_response.hpp"

namespace shared_model {
  namespace interface {
    /**
     * Response with all permissions related to role
     */
    class RolePermissionsResponse
        : public Hashable<RolePermissionsResponse,
                          iroha::model::RolePermissionsResponse> {
     public:
      /**
       * @return role permissions
       */
      virtual const types::RolePermissionsType &rolePermissions() const = 0;

      /**
       * Stringify the data.
       * @return string representation of data.
       */
      virtual std::string toString() const override {
        std::string s = "RolePermissionsResponse:{";
        s += "rolePermissions:"
            + boost::algorithm::join(rolePermissions().begin(), ",");
        s += "}";
        return s;
      }

      /**
       * @return hash of object.
       * Equality of hashes means equality of objects.
       */
      virtual const HashType &hash() const override;

      /**
       * Implementation of operator ==
       * @param rhs - the right hand-side of RolePermissionsResponse
       * @return true if they have same values.
       */
      bool operator==(const ModelType &rhs) const override {
        return rolePermissions() == rhs.rolePermissions();
      }

      /**
       * Makes old model.
       * @return An allocated old model of role permissions response.
       */
      [[deprecated]] virtual OldModelType *makeOldModel() const override {
        OldModelType *oldModel = new OldModelType();
        oldModel->role_permissions = rolePermissions();
        return oldModel;
      }
    };

    /**
     * Provide response with all roles of the current system
     */
    class RolesResponse
        : public Hashable<RolesResponse, iroha::model::RolesResponse> {
     public:
      /**
       * @return all roles of the current system
       */
      virtual const types::RolesType &roles() const = 0;

      /**
       * Stringify the data.
       * @return string representation of data.
       */
      virtual std::string toString() const override {
        std::string s = "RolesResponse:{";
        s += "Roles:" + boost::algorithm::join(roles().begin(), ",");
        s += "}";
        return s;
      }

      /**
       * @return hash of object.
       * Equality of hashes means equality of objects.
       */
      virtual const HashType &hash() const override;

      /**
       * operator ==
       * @return true if the data are same.
       */
      virtual bool operator==(const ModelType &rhs) const override {
        return roles() == rhs.roles();
      }

      /**
       * Makes old model.
       * @return An allocated old model of roles response.
       */
      [[deprecated]] virtual OldModelType *makeOldModel() const override {
        OldModelType *oldModel = new OldModelType();
        oldModel->roles = roles();
        return oldModel;
      }
    };
  }  // namespace interface
}  // namespace shared_model
#endif  // IROHA_SHARED_MODEL_ROLES_RESPONSE_HPP
