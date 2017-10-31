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

#ifndef IROHA_SHARED_MODEL_ERROR_RESPONSE_HPP
#define IROHA_SHARED_MODEL_ERROR_RESPONSE_HPP

#include <boost/assert.hpp>
#include "crypto/hash.hpp"
#include "interfaces/common_objects/types.hpp"
#include "interfaces/hashable.hpp"
#include "interfaces/queries/responses/error_response.hpp"
#include "model/queries/response/error_response.hpp"

namespace shared_model {
  namespace interface {
    /**
     * Provide error answer with reason about error
     */
    class ErrorResponse
        : public Hashable<ErrorResponse, iroha::model::ErrorResponse> {
     public:
      ~ErrorResponse() override {}
      /**
       * Reason of error
       */
      enum class Reason {
        /**
         * signatures or created time are invalid
         */
        STATELESS_INVALID,
        /**
         * permissions are invalid
         */
        STATEFUL_INVALID,
        /**
         * when requested account does not exist
         */
        NO_ACCOUNT,
        /**
         * when requested asset does not exist
         */
        NO_ASSET,
        /**
         * No Roles found in the system
         */
        NO_ROLES,
        /**
         * when requested account asset does not exist
         */
        NO_ACCOUNT_ASSETS,
        /**
         * when requested signatories does not exist
         */
        NO_SIGNATORIES,
        /**
         * when unidentified request was received
         */
        NOT_SUPPORTED
      };

      /**
       * Error reason for failing in fetching data.
       * @return Error reason
       */
      virtual const Reason &reason() = 0;

      /**
       * Stringify the data.
       * @return the content of error response.
       */
      virtual std::string toString() const override {
        std::string reason;
        switch (reason()) {
          case Reason::STATELESS_INVALID: {
            reason = "STATELESS_INVALID";
            break;
          }
          case Reason::STATEFUL_INVALID: {
            reason = "STATEFUL_INVALID";
            break;
          }
          case Reason::NO_ACCOUNT: {
            reason = "NO_ACCOUNT";
            break;
          }
          case Reason::NO_ASSET: {
            reason = "NO_ASSET";
            break;
          }
          case Reason::NO_ROLES: {
            reason = "NO_ROLES";
            break;
          }
          case Reason::NO_ACCOUNT_ASSETS: {
            reason = "NO_ACCOUNT_ASSETS";
            break;
          }
          case Reason::NO_SIGNATORIES: {
            reason = "NO_SIGNATORIES";
            break;
          }
          case Reason::NOT_SUPPORTED: {
            reason = "NOT_SUPPORTED";
            break;
          }
          default: {
            BOOST_ASSERT_MSG(false,
                             "shared_model::ErrorResponse::toString(): Not "
                             "found matched enum");
          }
        }

        std::string s = "ErrorResponse:{";
        s += "Reason:" + reason;
        s += "}";
        return s;
      }

      /**
       * Stringify the data.
       * @return string representation of data.
       */
      virtual const HashType &hash() const override;

      /**
       * Implementation of operator ==
       * @param rhs - the right hand-side of ErrorResponse object
       * @return true if they have same values.
       */
      bool operator==(const ModelType &rhs) const override {
        return reason() == rhs.reason();
      }

      /**
       * Makes old model.
       * @return An allocated old model of error response.
       */
      [[deprecated]] virtual OldModelType *makeOldModel() const override {
        switch (reason()) {
          case Reason::STATELESS_INVALID: {
            return OldModelType::STATELESS_INVALID;
          }
          case Reason::STATEFUL_INVALID: {
            return OldModelType::STATEFUL_INVALID;
          }
          case Reason::NO_ACCOUNT: {
            return OldModelType::NO_ACCOUNT;
          }
          case Reason::NO_ASSET: {
            return OldModelType::NO_ASSET;
          }
          case Reason::NO_ROLES: {
            return OldModelType::NO_ROLES;
          }
          case Reason::NO_ACCOUNT_ASSETS: {
            return OldModelType::NO_ACCOUNT_ASSETS;
          }
          case Reason::NO_SIGNATORIES: {
            return OldModelType::NO_SIGNATORIES;
          }
          case Reason::NOT_SUPPORTED: {
            return OldModelType::NOT_SUPPORTED;
          }
          default: {
            BOOST_ASSERT_MSG(false,
                             "shared_model::ErrorResponse::makeOldModel(): Not "
                             "found matched enum");
          }
        }
      }
    };
  }  // namespace interface
}  // namespace shared_model
#endif  // IROHA_SHARED_MODEL_ERROR_RESPONSE_HPP
