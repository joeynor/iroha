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

#ifndef IROHA_SHARED_MODEL_SIGNATORIES_RESPONSE_HPP
#define IROHA_SHARED_MODEL_SIGNATORIES_RESPONSE_HPP

#include <boost/algorithm/string/join.hpp>
#include "interfaces/common_objects/types.hpp"
#include "interfaces/hashable.hpp"
#include "interfaces/queries/responses/signatories_response.hpp"
#include "model/queries/responses/signatories_response.hpp"

namespace shared_model {
  namespace interface {
    /**
     * Container of asset, for fetching data.
     */
    class SignatoriesResponse
        : public Hashable<SignatoriesResponse,
                          iroha::model::SignatoriesResponse> {
     public:
      /**
       * @return All public keys attached to account
       */
      virtual const types::KeysType &keys() const = 0;

      /**
       * Stringify the data.
       * @return string representation of data.
       */
      virtual std::string toString() const override {
        std::string s = "SignatoriesResponse:{";
        s += "keys:" + boost::algorithm::join(keys().begin(), ",");
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
        return keys() == rhs.keys();
      }

      /**
       * Makes old model.
       * @return An allocated old model of signatories response.
       */
      [[deprecated]] virtual OldModelType *makeOldModel() const override {
        OldModelType *oldModel = new OldModelType();
        oldModel->keys = keys();
        return oldModel;
      }
    };
  }  // namespace interface
}  // namespace shared_model
#endif  // IROHA_SHARED_MODEL_SIGNATORIES_RESPONSE_HPP
