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

#ifndef IROHA_SHARED_MODEL_ACCOUNT_ASSET_RESPONSE_HPP
#define IROHA_SHARED_MODEL_ACCOUNT_ASSET_RESPONSE_HPP

#include "interfaces/common_objects/types.hpp"
#include "interfaces/hashable.hpp"
#include "interfaces/account_asset.hpp"
#include "model/queries/responses/account_assets_response.hpp"

namespace shared_model {
  namespace interface {
    class AccountAssetResponse
        : public Hashable<AccountAssetResponse,
                          iroha::model::AccountAssetResponse> {
     public:
      /**
       * @return Account has Asset model
       */
      virtual const AccountAsset &accountAsset() const = 0;

      /**
       * Stringify the data.
       * @return the content of account asset response.
       */
      virtual std::string toString() const override {
        std::string s = "AccountAssetResponse:{";
        s += "AccountAsset:" + accountAsset().toString();
        s += "}";
        return s;
      }

      /**
       * Makes old model.
       * @return An allocated old model of account asset response.
       */
      [[deprecated]] virtual OldModelType *makeOldModel() const override {
        OldModelType *oldModel = new OldModelType();
        oldModel->acct_asset = *accountAsset().makeOldModel();
        return oldModel;
      }
    };
  }  // namespace interface
}  // namespace shared_model
#endif  // IROHA_SHARED_MODEL_ACCOUNT_ASSET_RESPONSE_HPP
