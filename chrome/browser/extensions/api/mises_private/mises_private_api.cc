#include "chrome/browser/extensions/api/mises_private/mises_private_api.h"
#include "chrome/browser/extensions/chrome_extension_function.h"
#include "extensions/browser/extension_function_registry.h"
#include "extensions/common/extension.h"
#include "base/logging.h"
#include "chrome/browser/android/mises/mises_controller.h"
#include "base/android/sys_utils.h"
#include "base/android/application_status_listener.h"

namespace extensions {
MisesPrivateSetMisesIdFunction::~MisesPrivateSetMisesIdFunction() {}
 
bool MisesPrivateSetMisesIdFunction::RunAsync() {
  std::unique_ptr<api::mises_private::SetMisesId::Params> params(
      api::mises_private::SetMisesId::Params::Create(*args_));
  EXTENSION_FUNCTION_VALIDATE(params.get());
  LOG(INFO) << "set mises id :" << params->id;
  android::MisesController::GetInstance()->setMisesUserInfo(params->id);
  SendResponse(true);
  return true;
}

MisesPrivateGetInstallReferrerFunction::~MisesPrivateGetInstallReferrerFunction() {}
ExtensionFunction::ResponseAction MisesPrivateGetInstallReferrerFunction::Run() {
  std::string referrerString = base::android::SysUtils::ReferrerStringFromJni();
  return RespondNow(ArgumentList(
    api::mises_private::GetInstallReferrer::Results::Create(referrerString)));
}

MisesPrivateGetAppStateFunction::~MisesPrivateGetAppStateFunction() {}
ExtensionFunction::ResponseAction MisesPrivateGetAppStateFunction::Run() {
  api::mises_private::AppState state = api::mises_private::AppState::APP_STATE_NONE;
  switch (base::android::ApplicationStatusListener::GetState()) {
    case base::android::ApplicationState::APPLICATION_STATE_UNKNOWN :{
      state = api::mises_private::AppState::APP_STATE_UNKNOWN;
      break;
    }
    case base::android::ApplicationState::APPLICATION_STATE_HAS_RUNNING_ACTIVITIES :{
      state = api::mises_private::AppState::APP_STATE_RUNNING;
      break;
    }
    case base::android::ApplicationState::APPLICATION_STATE_HAS_PAUSED_ACTIVITIES :{
      state = api::mises_private::AppState::APP_STATE_PAUSED;
      break;
    }
    case base::android::ApplicationState::APPLICATION_STATE_HAS_STOPPED_ACTIVITIES :{
      state = api::mises_private::AppState::APP_STATE_STOPPED;
      break;
    }
    case base::android::ApplicationState::APPLICATION_STATE_HAS_DESTROYED_ACTIVITIES :{
      state = api::mises_private::AppState::APP_STATE_DESTROYED;
      break;
    }
  }
  return RespondNow(ArgumentList(
    api::mises_private::GetAppState::Results::Create(state)));
}


}  // namespace extensions
