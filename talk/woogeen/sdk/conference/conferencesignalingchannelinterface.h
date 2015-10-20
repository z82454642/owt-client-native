/*
 * Intel License
 */

#ifndef WOOGEEN_CONFERENCE_SIGNALINGCHANNELINTERFACE_H_
#define WOOGEEN_CONFERENCE_SIGNALINGCHANNELINTERFACE_H_

#include <functional>
#include <memory>
#include "talk/woogeen/sdk/conference/conferenceexception.h"
#include "talk/woogeen/sdk/conference/conferenceuser.h"
#include "webrtc/base/json.h"

namespace woogeen {
class ConferenceSignalingChannelObserver {
 public:
  virtual void OnStreamAdded(Json::Value stream) = 0;
  virtual void OnUserJoined(
      std::shared_ptr<const woogeen::conference::User> user) = 0;
  virtual void OnUserLeft(
      std::shared_ptr<const woogeen::conference::User> user) = 0;
  virtual void OnStreamRemoved(Json::Value stream) = 0;
  virtual void OnServerDisconnected() = 0;
  virtual void OnCustomMessage(std::string& from, std::string& message) = 0;
};

class ConferenceSignalingChannelInterface {
 public:
  virtual void AddObserver(ConferenceSignalingChannelObserver& observer) = 0;
  virtual void RemoveObserver(ConferenceSignalingChannelObserver& observer) = 0;

  virtual void Connect(
      const std::string& token,
      std::function<void(Json::Value& room_info,
                         std::vector<const conference::User> users)> on_success,
      std::function<void(std::unique_ptr<ConferenceException>)> on_failure) = 0;
  virtual void SendSdp(
      Json::Value& options,
      std::string& sdp,
      bool is_publish,
      std::function<void(Json::Value& ack, std::string& stream_id)> on_success,
      std::function<void(std::unique_ptr<ConferenceException>)> on_failure) = 0;
  virtual void SendStreamEvent(
      const std::string& event,
      const std::string& stream_id,
      std::function<void()> on_success,
      std::function<void(std::unique_ptr<ConferenceException>)> on_failure) = 0;
  virtual void SendCustomMessage(
      const std::string& message,
      const std::string& receiver,
      std::function<void()> on_success,
      std::function<void(std::unique_ptr<ConferenceException>)> on_failure) = 0;
  virtual void SendStreamControlMessage(
      const std::string& stream_id,
      const std::string& action,
      std::function<void()> on_success,
      std::function<void(std::unique_ptr<ConferenceException>)> on_failure) = 0;
  virtual void Disconnect(
      std::function<void()> on_success,
      std::function<void(std::unique_ptr<ConferenceException>)> on_failure) = 0;
};
}

#endif  // WOOGEEN_CONFERENCE_SIGNALINGCHANNELINTERFACE_H_