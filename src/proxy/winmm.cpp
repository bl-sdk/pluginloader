#include "proxy.h"
#include "util.h"

// Modified copy of  https://github.com/Erik-JS/proxy-dll-64/blob/master/winmm/main.cpp

namespace pluginloader::proxy {

namespace {

HMODULE winmm_dll_handle = nullptr;

FARPROC winmm_close_driver = nullptr;
FARPROC winmm_def_driver_proc = nullptr;
FARPROC winmm_driver_callback = nullptr;
FARPROC winmm_drv_get_module_handle = nullptr;
FARPROC winmm_get_driver_module_handle = nullptr;
FARPROC winmm_open_driver = nullptr;
FARPROC winmm_play_sound = nullptr;
FARPROC winmm_play_sound_a = nullptr;
FARPROC winmm_play_sound_w = nullptr;
FARPROC winmm_send_driver_message = nullptr;
FARPROC winmm_wow_app_exit = nullptr;
FARPROC winmm_aux_get_dev_caps_a = nullptr;
FARPROC winmm_aux_get_dev_caps_w = nullptr;
FARPROC winmm_aux_get_num_devs = nullptr;
FARPROC winmm_aux_get_volume = nullptr;
FARPROC winmm_aux_out_message = nullptr;
FARPROC winmm_aux_set_volume = nullptr;
FARPROC winmm_joy_config_changed = nullptr;
FARPROC winmm_joy_get_dev_caps_a = nullptr;
FARPROC winmm_joy_get_dev_caps_w = nullptr;
FARPROC winmm_joy_get_num_devs = nullptr;
FARPROC winmm_joy_get_pos = nullptr;
FARPROC winmm_joy_get_pos_ex = nullptr;
FARPROC winmm_joy_get_threshold = nullptr;
FARPROC winmm_joy_release_capture = nullptr;
FARPROC winmm_joy_set_capture = nullptr;
FARPROC winmm_joy_set_threshold = nullptr;
FARPROC winmm_mci_driver_notify = nullptr;
FARPROC winmm_mci_driver_yield = nullptr;
FARPROC winmm_mci_execute = nullptr;
FARPROC winmm_mci_free_command_resource = nullptr;
FARPROC winmm_mci_get_creator_task = nullptr;
FARPROC winmm_mci_get_device_id_a = nullptr;
FARPROC winmm_mci_get_device_id_from_element_id_a = nullptr;
FARPROC winmm_mci_get_device_id_from_element_id_w = nullptr;
FARPROC winmm_mci_get_device_id_w = nullptr;
FARPROC winmm_mci_get_driver_data = nullptr;
FARPROC winmm_mci_get_error_string_a = nullptr;
FARPROC winmm_mci_get_error_string_w = nullptr;
FARPROC winmm_mci_get_yield_proc = nullptr;
FARPROC winmm_mci_load_command_resource = nullptr;
FARPROC winmm_mci_send_command_a = nullptr;
FARPROC winmm_mci_send_command_w = nullptr;
FARPROC winmm_mci_send_string_a = nullptr;
FARPROC winmm_mci_send_string_w = nullptr;
FARPROC winmm_mci_set_driver_data = nullptr;
FARPROC winmm_mci_set_yield_proc = nullptr;
FARPROC winmm_midi_connect = nullptr;
FARPROC winmm_midi_disconnect = nullptr;
FARPROC winmm_midi_in_add_buffer = nullptr;
FARPROC winmm_midi_in_close = nullptr;
FARPROC winmm_midi_in_get_dev_caps_a = nullptr;
FARPROC winmm_midi_in_get_dev_caps_w = nullptr;
FARPROC winmm_midi_in_get_error_text_a = nullptr;
FARPROC winmm_midi_in_get_error_text_w = nullptr;
FARPROC winmm_midi_in_get_id = nullptr;
FARPROC winmm_midi_in_get_num_devs = nullptr;
FARPROC winmm_midi_in_message = nullptr;
FARPROC winmm_midi_in_open = nullptr;
FARPROC winmm_midi_in_prepare_header = nullptr;
FARPROC winmm_midi_in_reset = nullptr;
FARPROC winmm_midi_in_start = nullptr;
FARPROC winmm_midi_in_stop = nullptr;
FARPROC winmm_midi_in_unprepare_header = nullptr;
FARPROC winmm_midi_out_cache_drum_patches = nullptr;
FARPROC winmm_midi_out_cache_patches = nullptr;
FARPROC winmm_midi_out_close = nullptr;
FARPROC winmm_midi_out_get_dev_caps_a = nullptr;
FARPROC winmm_midi_out_get_dev_caps_w = nullptr;
FARPROC winmm_midi_out_get_error_text_a = nullptr;
FARPROC winmm_midi_out_get_error_text_w = nullptr;
FARPROC winmm_midi_out_get_id = nullptr;
FARPROC winmm_midi_out_get_num_devs = nullptr;
FARPROC winmm_midi_out_get_volume = nullptr;
FARPROC winmm_midi_out_long_msg = nullptr;
FARPROC winmm_midi_out_message = nullptr;
FARPROC winmm_midi_out_open = nullptr;
FARPROC winmm_midi_out_prepare_header = nullptr;
FARPROC winmm_midi_out_reset = nullptr;
FARPROC winmm_midi_out_set_volume = nullptr;
FARPROC winmm_midi_out_short_msg = nullptr;
FARPROC winmm_midi_out_unprepare_header = nullptr;
FARPROC winmm_midi_stream_close = nullptr;
FARPROC winmm_midi_stream_open = nullptr;
FARPROC winmm_midi_stream_out = nullptr;
FARPROC winmm_midi_stream_pause = nullptr;
FARPROC winmm_midi_stream_position = nullptr;
FARPROC winmm_midi_stream_property = nullptr;
FARPROC winmm_midi_stream_restart = nullptr;
FARPROC winmm_midi_stream_stop = nullptr;
FARPROC winmm_mixer_close = nullptr;
FARPROC winmm_mixer_get_control_details_a = nullptr;
FARPROC winmm_mixer_get_control_details_w = nullptr;
FARPROC winmm_mixer_get_dev_caps_a = nullptr;
FARPROC winmm_mixer_get_dev_caps_w = nullptr;
FARPROC winmm_mixer_get_id = nullptr;
FARPROC winmm_mixer_get_line_controls_a = nullptr;
FARPROC winmm_mixer_get_line_controls_w = nullptr;
FARPROC winmm_mixer_get_line_info_a = nullptr;
FARPROC winmm_mixer_get_line_info_w = nullptr;
FARPROC winmm_mixer_get_num_devs = nullptr;
FARPROC winmm_mixer_message = nullptr;
FARPROC winmm_mixer_open = nullptr;
FARPROC winmm_mixer_set_control_details = nullptr;
FARPROC winmm_mm_drv_install = nullptr;
FARPROC winmm_mm_get_current_task = nullptr;
FARPROC winmm_mm_task_block = nullptr;
FARPROC winmm_mm_task_create = nullptr;
FARPROC winmm_mm_task_signal = nullptr;
FARPROC winmm_mm_task_yield = nullptr;
FARPROC winmm_mmio_advance = nullptr;
FARPROC winmm_mmio_ascend = nullptr;
FARPROC winmm_mmio_close = nullptr;
FARPROC winmm_mmio_create_chunk = nullptr;
FARPROC winmm_mmio_descend = nullptr;
FARPROC winmm_mmio_flush = nullptr;
FARPROC winmm_mmio_get_info = nullptr;
FARPROC winmm_mmio_install_io_proc_a = nullptr;
FARPROC winmm_mmio_install_io_proc_w = nullptr;
FARPROC winmm_mmio_open_a = nullptr;
FARPROC winmm_mmio_open_w = nullptr;
FARPROC winmm_mmio_read = nullptr;
FARPROC winmm_mmio_rename_a = nullptr;
FARPROC winmm_mmio_rename_w = nullptr;
FARPROC winmm_mmio_seek = nullptr;
FARPROC winmm_mmio_send_message = nullptr;
FARPROC winmm_mmio_set_buffer = nullptr;
FARPROC winmm_mmio_set_info = nullptr;
FARPROC winmm_mmio_string_to_fourcc_a = nullptr;
FARPROC winmm_mmio_string_to_fourcc_w = nullptr;
FARPROC winmm_mmio_write = nullptr;
FARPROC winmm_mmsystem_get_version = nullptr;
FARPROC winmm_snd_play_sound_a = nullptr;
FARPROC winmm_snd_play_sound_w = nullptr;
FARPROC winmm_time_begin_period = nullptr;
FARPROC winmm_time_end_period = nullptr;
FARPROC winmm_time_get_dev_caps = nullptr;
FARPROC winmm_time_get_system_time = nullptr;
FARPROC winmm_time_get_time = nullptr;
FARPROC winmm_time_kill_event = nullptr;
FARPROC winmm_time_set_event = nullptr;
FARPROC winmm_wave_in_add_buffer = nullptr;
FARPROC winmm_wave_in_close = nullptr;
FARPROC winmm_wave_in_get_dev_caps_a = nullptr;
FARPROC winmm_wave_in_get_dev_caps_w = nullptr;
FARPROC winmm_wave_in_get_error_text_a = nullptr;
FARPROC winmm_wave_in_get_error_text_w = nullptr;
FARPROC winmm_wave_in_get_id = nullptr;
FARPROC winmm_wave_in_get_num_devs = nullptr;
FARPROC winmm_wave_in_get_position = nullptr;
FARPROC winmm_wave_in_message = nullptr;
FARPROC winmm_wave_in_open = nullptr;
FARPROC winmm_wave_in_prepare_header = nullptr;
FARPROC winmm_wave_in_reset = nullptr;
FARPROC winmm_wave_in_start = nullptr;
FARPROC winmm_wave_in_stop = nullptr;
FARPROC winmm_wave_in_unprepare_header = nullptr;
FARPROC winmm_wave_out_break_loop = nullptr;
FARPROC winmm_wave_out_close = nullptr;
FARPROC winmm_wave_out_get_dev_caps_a = nullptr;
FARPROC winmm_wave_out_get_dev_caps_w = nullptr;
FARPROC winmm_wave_out_get_error_text_a = nullptr;
FARPROC winmm_wave_out_get_error_text_w = nullptr;
FARPROC winmm_wave_out_get_id = nullptr;
FARPROC winmm_wave_out_get_num_devs = nullptr;
FARPROC winmm_wave_out_get_pitch = nullptr;
FARPROC winmm_wave_out_get_playback_rate = nullptr;
FARPROC winmm_wave_out_get_position = nullptr;
FARPROC winmm_wave_out_get_volume = nullptr;
FARPROC winmm_wave_out_message = nullptr;
FARPROC winmm_wave_out_open = nullptr;
FARPROC winmm_wave_out_pause = nullptr;
FARPROC winmm_wave_out_prepare_header = nullptr;
FARPROC winmm_wave_out_reset = nullptr;
FARPROC winmm_wave_out_restart = nullptr;
FARPROC winmm_wave_out_set_pitch = nullptr;
FARPROC winmm_wave_out_set_playback_rate = nullptr;
FARPROC winmm_wave_out_set_volume = nullptr;
FARPROC winmm_wave_out_unprepare_header = nullptr;
FARPROC winmm_wave_out_write = nullptr;

}  // namespace

// NOLINTBEGIN(readability-identifier-naming, readability-avoid-return-with-void-value)
// clang-format off
DLL_EXPORT void CloseDriver() { return reinterpret_cast<decltype(&CloseDriver)>(winmm_close_driver)(); }
DLL_EXPORT void DefDriverProc() { return reinterpret_cast<decltype(&DefDriverProc)>(winmm_def_driver_proc)(); }
DLL_EXPORT void DriverCallback() { return reinterpret_cast<decltype(&DriverCallback)>(winmm_driver_callback)(); }
DLL_EXPORT void DrvGetModuleHandle() { return reinterpret_cast<decltype(&DrvGetModuleHandle)>(winmm_drv_get_module_handle)(); }
DLL_EXPORT void GetDriverModuleHandle() { return reinterpret_cast<decltype(&GetDriverModuleHandle)>(winmm_get_driver_module_handle)(); }
DLL_EXPORT void OpenDriver() { return reinterpret_cast<decltype(&OpenDriver)>(winmm_open_driver)(); }
DLL_EXPORT void PlaySound() { return reinterpret_cast<decltype(&PlaySound)>(winmm_play_sound)(); }
DLL_EXPORT void PlaySoundA() { return reinterpret_cast<decltype(&PlaySoundA)>(winmm_play_sound_a)(); }
DLL_EXPORT void PlaySoundW() { return reinterpret_cast<decltype(&PlaySoundW)>(winmm_play_sound_w)(); }
DLL_EXPORT void SendDriverMessage() { return reinterpret_cast<decltype(&SendDriverMessage)>(winmm_send_driver_message)(); }
DLL_EXPORT void WOWAppExit() { return reinterpret_cast<decltype(&WOWAppExit)>(winmm_wow_app_exit)(); }
DLL_EXPORT void auxGetDevCapsA() { return reinterpret_cast<decltype(&auxGetDevCapsA)>(winmm_aux_get_dev_caps_a)(); }
DLL_EXPORT void auxGetDevCapsW() { return reinterpret_cast<decltype(&auxGetDevCapsW)>(winmm_aux_get_dev_caps_w)(); }
DLL_EXPORT void auxGetNumDevs() { return reinterpret_cast<decltype(&auxGetNumDevs)>(winmm_aux_get_num_devs)(); }
DLL_EXPORT void auxGetVolume() { return reinterpret_cast<decltype(&auxGetVolume)>(winmm_aux_get_volume)(); }
DLL_EXPORT void auxOutMessage() { return reinterpret_cast<decltype(&auxOutMessage)>(winmm_aux_out_message)(); }
DLL_EXPORT void auxSetVolume() { return reinterpret_cast<decltype(&auxSetVolume)>(winmm_aux_set_volume)(); }
DLL_EXPORT void joyConfigChanged() { return reinterpret_cast<decltype(&joyConfigChanged)>(winmm_joy_config_changed)(); }
DLL_EXPORT void joyGetDevCapsA() { return reinterpret_cast<decltype(&joyGetDevCapsA)>(winmm_joy_get_dev_caps_a)(); }
DLL_EXPORT void joyGetDevCapsW() { return reinterpret_cast<decltype(&joyGetDevCapsW)>(winmm_joy_get_dev_caps_w)(); }
DLL_EXPORT void joyGetNumDevs() { return reinterpret_cast<decltype(&joyGetNumDevs)>(winmm_joy_get_num_devs)(); }
DLL_EXPORT void joyGetPos() { return reinterpret_cast<decltype(&joyGetPos)>(winmm_joy_get_pos)(); }
DLL_EXPORT void joyGetPosEx() { return reinterpret_cast<decltype(&joyGetPosEx)>(winmm_joy_get_pos_ex)(); }
DLL_EXPORT void joyGetThreshold() { return reinterpret_cast<decltype(&joyGetThreshold)>(winmm_joy_get_threshold)(); }
DLL_EXPORT void joyReleaseCapture() { return reinterpret_cast<decltype(&joyReleaseCapture)>(winmm_joy_release_capture)(); }
DLL_EXPORT void joySetCapture() { return reinterpret_cast<decltype(&joySetCapture)>(winmm_joy_set_capture)(); }
DLL_EXPORT void joySetThreshold() { return reinterpret_cast<decltype(&joySetThreshold)>(winmm_joy_set_threshold)(); }
DLL_EXPORT void mciDriverNotify() { return reinterpret_cast<decltype(&mciDriverNotify)>(winmm_mci_driver_notify)(); }
DLL_EXPORT void mciDriverYield() { return reinterpret_cast<decltype(&mciDriverYield)>(winmm_mci_driver_yield)(); }
DLL_EXPORT void mciExecute() { return reinterpret_cast<decltype(&mciExecute)>(winmm_mci_execute)(); }
DLL_EXPORT void mciFreeCommandResource() { return reinterpret_cast<decltype(&mciFreeCommandResource)>(winmm_mci_free_command_resource)(); }
DLL_EXPORT void mciGetCreatorTask() { return reinterpret_cast<decltype(&mciGetCreatorTask)>(winmm_mci_get_creator_task)(); }
DLL_EXPORT void mciGetDeviceIDA() { return reinterpret_cast<decltype(&mciGetDeviceIDA)>(winmm_mci_get_device_id_a)(); }
DLL_EXPORT void mciGetDeviceIDFromElementIDA() { return reinterpret_cast<decltype(&mciGetDeviceIDFromElementIDA)>(winmm_mci_get_device_id_from_element_id_a)(); }
DLL_EXPORT void mciGetDeviceIDFromElementIDW() { return reinterpret_cast<decltype(&mciGetDeviceIDFromElementIDW)>(winmm_mci_get_device_id_from_element_id_w)(); }
DLL_EXPORT void mciGetDeviceIDW() { return reinterpret_cast<decltype(&mciGetDeviceIDW)>(winmm_mci_get_device_id_w)(); }
DLL_EXPORT void mciGetDriverData() { return reinterpret_cast<decltype(&mciGetDriverData)>(winmm_mci_get_driver_data)(); }
DLL_EXPORT void mciGetErrorStringA() { return reinterpret_cast<decltype(&mciGetErrorStringA)>(winmm_mci_get_error_string_a)(); }
DLL_EXPORT void mciGetErrorStringW() { return reinterpret_cast<decltype(&mciGetErrorStringW)>(winmm_mci_get_error_string_w)(); }
DLL_EXPORT void mciGetYieldProc() { return reinterpret_cast<decltype(&mciGetYieldProc)>(winmm_mci_get_yield_proc)(); }
DLL_EXPORT void mciLoadCommandResource() { return reinterpret_cast<decltype(&mciLoadCommandResource)>(winmm_mci_load_command_resource)(); }
DLL_EXPORT void mciSendCommandA() { return reinterpret_cast<decltype(&mciSendCommandA)>(winmm_mci_send_command_a)(); }
DLL_EXPORT void mciSendCommandW() { return reinterpret_cast<decltype(&mciSendCommandW)>(winmm_mci_send_command_w)(); }
DLL_EXPORT void mciSendStringA() { return reinterpret_cast<decltype(&mciSendStringA)>(winmm_mci_send_string_a)(); }
DLL_EXPORT void mciSendStringW() { return reinterpret_cast<decltype(&mciSendStringW)>(winmm_mci_send_string_w)(); }
DLL_EXPORT void mciSetDriverData() { return reinterpret_cast<decltype(&mciSetDriverData)>(winmm_mci_set_driver_data)(); }
DLL_EXPORT void mciSetYieldProc() { return reinterpret_cast<decltype(&mciSetYieldProc)>(winmm_mci_set_yield_proc)(); }
DLL_EXPORT void midiConnect() { return reinterpret_cast<decltype(&midiConnect)>(winmm_midi_connect)(); }
DLL_EXPORT void midiDisconnect() { return reinterpret_cast<decltype(&midiDisconnect)>(winmm_midi_disconnect)(); }
DLL_EXPORT void midiInAddBuffer() { return reinterpret_cast<decltype(&midiInAddBuffer)>(winmm_midi_in_add_buffer)(); }
DLL_EXPORT void midiInClose() { return reinterpret_cast<decltype(&midiInClose)>(winmm_midi_in_close)(); }
DLL_EXPORT void midiInGetDevCapsA() { return reinterpret_cast<decltype(&midiInGetDevCapsA)>(winmm_midi_in_get_dev_caps_a)(); }
DLL_EXPORT void midiInGetDevCapsW() { return reinterpret_cast<decltype(&midiInGetDevCapsW)>(winmm_midi_in_get_dev_caps_w)(); }
DLL_EXPORT void midiInGetErrorTextA() { return reinterpret_cast<decltype(&midiInGetErrorTextA)>(winmm_midi_in_get_error_text_a)(); }
DLL_EXPORT void midiInGetErrorTextW() { return reinterpret_cast<decltype(&midiInGetErrorTextW)>(winmm_midi_in_get_error_text_w)(); }
DLL_EXPORT void midiInGetID() { return reinterpret_cast<decltype(&midiInGetID)>(winmm_midi_in_get_id)(); }
DLL_EXPORT void midiInGetNumDevs() { return reinterpret_cast<decltype(&midiInGetNumDevs)>(winmm_midi_in_get_num_devs)(); }
DLL_EXPORT void midiInMessage() { return reinterpret_cast<decltype(&midiInMessage)>(winmm_midi_in_message)(); }
DLL_EXPORT void midiInOpen() { return reinterpret_cast<decltype(&midiInOpen)>(winmm_midi_in_open)(); }
DLL_EXPORT void midiInPrepareHeader() { return reinterpret_cast<decltype(&midiInPrepareHeader)>(winmm_midi_in_prepare_header)(); }
DLL_EXPORT void midiInReset() { return reinterpret_cast<decltype(&midiInReset)>(winmm_midi_in_reset)(); }
DLL_EXPORT void midiInStart() { return reinterpret_cast<decltype(&midiInStart)>(winmm_midi_in_start)(); }
DLL_EXPORT void midiInStop() { return reinterpret_cast<decltype(&midiInStop)>(winmm_midi_in_stop)(); }
DLL_EXPORT void midiInUnprepareHeader() { return reinterpret_cast<decltype(&midiInUnprepareHeader)>(winmm_midi_in_unprepare_header)(); }
DLL_EXPORT void midiOutCacheDrumPatches() { return reinterpret_cast<decltype(&midiOutCacheDrumPatches)>(winmm_midi_out_cache_drum_patches)(); }
DLL_EXPORT void midiOutCachePatches() { return reinterpret_cast<decltype(&midiOutCachePatches)>(winmm_midi_out_cache_patches)(); }
DLL_EXPORT void midiOutClose() { return reinterpret_cast<decltype(&midiOutClose)>(winmm_midi_out_close)(); }
DLL_EXPORT void midiOutGetDevCapsA() { return reinterpret_cast<decltype(&midiOutGetDevCapsA)>(winmm_midi_out_get_dev_caps_a)(); }
DLL_EXPORT void midiOutGetDevCapsW() { return reinterpret_cast<decltype(&midiOutGetDevCapsW)>(winmm_midi_out_get_dev_caps_w)(); }
DLL_EXPORT void midiOutGetErrorTextA() { return reinterpret_cast<decltype(&midiOutGetErrorTextA)>(winmm_midi_out_get_error_text_a)(); }
DLL_EXPORT void midiOutGetErrorTextW() { return reinterpret_cast<decltype(&midiOutGetErrorTextW)>(winmm_midi_out_get_error_text_w)(); }
DLL_EXPORT void midiOutGetID() { return reinterpret_cast<decltype(&midiOutGetID)>(winmm_midi_out_get_id)(); }
DLL_EXPORT void midiOutGetNumDevs() { return reinterpret_cast<decltype(&midiOutGetNumDevs)>(winmm_midi_out_get_num_devs)(); }
DLL_EXPORT void midiOutGetVolume() { return reinterpret_cast<decltype(&midiOutGetVolume)>(winmm_midi_out_get_volume)(); }
DLL_EXPORT void midiOutLongMsg() { return reinterpret_cast<decltype(&midiOutLongMsg)>(winmm_midi_out_long_msg)(); }
DLL_EXPORT void midiOutMessage() { return reinterpret_cast<decltype(&midiOutMessage)>(winmm_midi_out_message)(); }
DLL_EXPORT void midiOutOpen() { return reinterpret_cast<decltype(&midiOutOpen)>(winmm_midi_out_open)(); }
DLL_EXPORT void midiOutPrepareHeader() { return reinterpret_cast<decltype(&midiOutPrepareHeader)>(winmm_midi_out_prepare_header)(); }
DLL_EXPORT void midiOutReset() { return reinterpret_cast<decltype(&midiOutReset)>(winmm_midi_out_reset)(); }
DLL_EXPORT void midiOutSetVolume() { return reinterpret_cast<decltype(&midiOutSetVolume)>(winmm_midi_out_set_volume)(); }
DLL_EXPORT void midiOutShortMsg() { return reinterpret_cast<decltype(&midiOutShortMsg)>(winmm_midi_out_short_msg)(); }
DLL_EXPORT void midiOutUnprepareHeader() { return reinterpret_cast<decltype(&midiOutUnprepareHeader)>(winmm_midi_out_unprepare_header)(); }
DLL_EXPORT void midiStreamClose() { return reinterpret_cast<decltype(&midiStreamClose)>(winmm_midi_stream_close)(); }
DLL_EXPORT void midiStreamOpen() { return reinterpret_cast<decltype(&midiStreamOpen)>(winmm_midi_stream_open)(); }
DLL_EXPORT void midiStreamOut() { return reinterpret_cast<decltype(&midiStreamOut)>(winmm_midi_stream_out)(); }
DLL_EXPORT void midiStreamPause() { return reinterpret_cast<decltype(&midiStreamPause)>(winmm_midi_stream_pause)(); }
DLL_EXPORT void midiStreamPosition() { return reinterpret_cast<decltype(&midiStreamPosition)>(winmm_midi_stream_position)(); }
DLL_EXPORT void midiStreamProperty() { return reinterpret_cast<decltype(&midiStreamProperty)>(winmm_midi_stream_property)(); }
DLL_EXPORT void midiStreamRestart() { return reinterpret_cast<decltype(&midiStreamRestart)>(winmm_midi_stream_restart)(); }
DLL_EXPORT void midiStreamStop() { return reinterpret_cast<decltype(&midiStreamStop)>(winmm_midi_stream_stop)(); }
DLL_EXPORT void mixerClose() { return reinterpret_cast<decltype(&mixerClose)>(winmm_mixer_close)(); }
DLL_EXPORT void mixerGetControlDetailsA() { return reinterpret_cast<decltype(&mixerGetControlDetailsA)>(winmm_mixer_get_control_details_a)(); }
DLL_EXPORT void mixerGetControlDetailsW() { return reinterpret_cast<decltype(&mixerGetControlDetailsW)>(winmm_mixer_get_control_details_w)(); }
DLL_EXPORT void mixerGetDevCapsA() { return reinterpret_cast<decltype(&mixerGetDevCapsA)>(winmm_mixer_get_dev_caps_a)(); }
DLL_EXPORT void mixerGetDevCapsW() { return reinterpret_cast<decltype(&mixerGetDevCapsW)>(winmm_mixer_get_dev_caps_w)(); }
DLL_EXPORT void mixerGetID() { return reinterpret_cast<decltype(&mixerGetID)>(winmm_mixer_get_id)(); }
DLL_EXPORT void mixerGetLineControlsA() { return reinterpret_cast<decltype(&mixerGetLineControlsA)>(winmm_mixer_get_line_controls_a)(); }
DLL_EXPORT void mixerGetLineControlsW() { return reinterpret_cast<decltype(&mixerGetLineControlsW)>(winmm_mixer_get_line_controls_w)(); }
DLL_EXPORT void mixerGetLineInfoA() { return reinterpret_cast<decltype(&mixerGetLineInfoA)>(winmm_mixer_get_line_info_a)(); }
DLL_EXPORT void mixerGetLineInfoW() { return reinterpret_cast<decltype(&mixerGetLineInfoW)>(winmm_mixer_get_line_info_w)(); }
DLL_EXPORT void mixerGetNumDevs() { return reinterpret_cast<decltype(&mixerGetNumDevs)>(winmm_mixer_get_num_devs)(); }
DLL_EXPORT void mixerMessage() { return reinterpret_cast<decltype(&mixerMessage)>(winmm_mixer_message)(); }
DLL_EXPORT void mixerOpen() { return reinterpret_cast<decltype(&mixerOpen)>(winmm_mixer_open)(); }
DLL_EXPORT void mixerSetControlDetails() { return reinterpret_cast<decltype(&mixerSetControlDetails)>(winmm_mixer_set_control_details)(); }
DLL_EXPORT void mmDrvInstall() { return reinterpret_cast<decltype(&mmDrvInstall)>(winmm_mm_drv_install)(); }
DLL_EXPORT void mmGetCurrentTask() { return reinterpret_cast<decltype(&mmGetCurrentTask)>(winmm_mm_get_current_task)(); }
DLL_EXPORT void mmTaskBlock() { return reinterpret_cast<decltype(&mmTaskBlock)>(winmm_mm_task_block)(); }
DLL_EXPORT void mmTaskCreate() { return reinterpret_cast<decltype(&mmTaskCreate)>(winmm_mm_task_create)(); }
DLL_EXPORT void mmTaskSignal() { return reinterpret_cast<decltype(&mmTaskSignal)>(winmm_mm_task_signal)(); }
DLL_EXPORT void mmTaskYield() { return reinterpret_cast<decltype(&mmTaskYield)>(winmm_mm_task_yield)(); }
DLL_EXPORT void mmioAdvance() { return reinterpret_cast<decltype(&mmioAdvance)>(winmm_mmio_advance)(); }
DLL_EXPORT void mmioAscend() { return reinterpret_cast<decltype(&mmioAscend)>(winmm_mmio_ascend)(); }
DLL_EXPORT void mmioClose() { return reinterpret_cast<decltype(&mmioClose)>(winmm_mmio_close)(); }
DLL_EXPORT void mmioCreateChunk() { return reinterpret_cast<decltype(&mmioCreateChunk)>(winmm_mmio_create_chunk)(); }
DLL_EXPORT void mmioDescend() { return reinterpret_cast<decltype(&mmioDescend)>(winmm_mmio_descend)(); }
DLL_EXPORT void mmioFlush() { return reinterpret_cast<decltype(&mmioFlush)>(winmm_mmio_flush)(); }
DLL_EXPORT void mmioGetInfo() { return reinterpret_cast<decltype(&mmioGetInfo)>(winmm_mmio_get_info)(); }
DLL_EXPORT void mmioInstallIOProcA() { return reinterpret_cast<decltype(&mmioInstallIOProcA)>(winmm_mmio_install_io_proc_a)(); }
DLL_EXPORT void mmioInstallIOProcW() { return reinterpret_cast<decltype(&mmioInstallIOProcW)>(winmm_mmio_install_io_proc_w)(); }
DLL_EXPORT void mmioOpenA() { return reinterpret_cast<decltype(&mmioOpenA)>(winmm_mmio_open_a)(); }
DLL_EXPORT void mmioOpenW() { return reinterpret_cast<decltype(&mmioOpenW)>(winmm_mmio_open_w)(); }
DLL_EXPORT void mmioRead() { return reinterpret_cast<decltype(&mmioRead)>(winmm_mmio_read)(); }
DLL_EXPORT void mmioRenameA() { return reinterpret_cast<decltype(&mmioRenameA)>(winmm_mmio_rename_a)(); }
DLL_EXPORT void mmioRenameW() { return reinterpret_cast<decltype(&mmioRenameW)>(winmm_mmio_rename_w)(); }
DLL_EXPORT void mmioSeek() { return reinterpret_cast<decltype(&mmioSeek)>(winmm_mmio_seek)(); }
DLL_EXPORT void mmioSendMessage() { return reinterpret_cast<decltype(&mmioSendMessage)>(winmm_mmio_send_message)(); }
DLL_EXPORT void mmioSetBuffer() { return reinterpret_cast<decltype(&mmioSetBuffer)>(winmm_mmio_set_buffer)(); }
DLL_EXPORT void mmioSetInfo() { return reinterpret_cast<decltype(&mmioSetInfo)>(winmm_mmio_set_info)(); }
DLL_EXPORT void mmioStringToFOURCCA() { return reinterpret_cast<decltype(&mmioStringToFOURCCA)>(winmm_mmio_string_to_fourcc_a)(); }
DLL_EXPORT void mmioStringToFOURCCW() { return reinterpret_cast<decltype(&mmioStringToFOURCCW)>(winmm_mmio_string_to_fourcc_w)(); }
DLL_EXPORT void mmioWrite() { return reinterpret_cast<decltype(&mmioWrite)>(winmm_mmio_write)(); }
DLL_EXPORT void mmsystemGetVersion() { return reinterpret_cast<decltype(&mmsystemGetVersion)>(winmm_mmsystem_get_version)(); }
DLL_EXPORT void sndPlaySoundA() { return reinterpret_cast<decltype(&sndPlaySoundA)>(winmm_snd_play_sound_a)(); }
DLL_EXPORT void sndPlaySoundW() { return reinterpret_cast<decltype(&sndPlaySoundW)>(winmm_snd_play_sound_w)(); }
DLL_EXPORT void timeBeginPeriod() { return reinterpret_cast<decltype(&timeBeginPeriod)>(winmm_time_begin_period)(); }
DLL_EXPORT void timeEndPeriod() { return reinterpret_cast<decltype(&timeEndPeriod)>(winmm_time_end_period)(); }
DLL_EXPORT void timeGetDevCaps() { return reinterpret_cast<decltype(&timeGetDevCaps)>(winmm_time_get_dev_caps)(); }
DLL_EXPORT void timeGetSystemTime() { return reinterpret_cast<decltype(&timeGetSystemTime)>(winmm_time_get_system_time)(); }
DLL_EXPORT void timeGetTime() { return reinterpret_cast<decltype(&timeGetTime)>(winmm_time_get_time)(); }
DLL_EXPORT void timeKillEvent() { return reinterpret_cast<decltype(&timeKillEvent)>(winmm_time_kill_event)(); }
DLL_EXPORT void timeSetEvent() { return reinterpret_cast<decltype(&timeSetEvent)>(winmm_time_set_event)(); }
DLL_EXPORT void waveInAddBuffer() { return reinterpret_cast<decltype(&waveInAddBuffer)>(winmm_wave_in_add_buffer)(); }
DLL_EXPORT void waveInClose() { return reinterpret_cast<decltype(&waveInClose)>(winmm_wave_in_close)(); }
DLL_EXPORT void waveInGetDevCapsA() { return reinterpret_cast<decltype(&waveInGetDevCapsA)>(winmm_wave_in_get_dev_caps_a)(); }
DLL_EXPORT void waveInGetDevCapsW() { return reinterpret_cast<decltype(&waveInGetDevCapsW)>(winmm_wave_in_get_dev_caps_w)(); }
DLL_EXPORT void waveInGetErrorTextA() { return reinterpret_cast<decltype(&waveInGetErrorTextA)>(winmm_wave_in_get_error_text_a)(); }
DLL_EXPORT void waveInGetErrorTextW() { return reinterpret_cast<decltype(&waveInGetErrorTextW)>(winmm_wave_in_get_error_text_w)(); }
DLL_EXPORT void waveInGetID() { return reinterpret_cast<decltype(&waveInGetID)>(winmm_wave_in_get_id)(); }
DLL_EXPORT void waveInGetNumDevs() { return reinterpret_cast<decltype(&waveInGetNumDevs)>(winmm_wave_in_get_num_devs)(); }
DLL_EXPORT void waveInGetPosition() { return reinterpret_cast<decltype(&waveInGetPosition)>(winmm_wave_in_get_position)(); }
DLL_EXPORT void waveInMessage() { return reinterpret_cast<decltype(&waveInMessage)>(winmm_wave_in_message)(); }
DLL_EXPORT void waveInOpen() { return reinterpret_cast<decltype(&waveInOpen)>(winmm_wave_in_open)(); }
DLL_EXPORT void waveInPrepareHeader() { return reinterpret_cast<decltype(&waveInPrepareHeader)>(winmm_wave_in_prepare_header)(); }
DLL_EXPORT void waveInReset() { return reinterpret_cast<decltype(&waveInReset)>(winmm_wave_in_reset)(); }
DLL_EXPORT void waveInStart() { return reinterpret_cast<decltype(&waveInStart)>(winmm_wave_in_start)(); }
DLL_EXPORT void waveInStop() { return reinterpret_cast<decltype(&waveInStop)>(winmm_wave_in_stop)(); }
DLL_EXPORT void waveInUnprepareHeader() { return reinterpret_cast<decltype(&waveInUnprepareHeader)>(winmm_wave_in_unprepare_header)(); }
DLL_EXPORT void waveOutBreakLoop() { return reinterpret_cast<decltype(&waveOutBreakLoop)>(winmm_wave_out_break_loop)(); }
DLL_EXPORT void waveOutClose() { return reinterpret_cast<decltype(&waveOutClose)>(winmm_wave_out_close)(); }
DLL_EXPORT void waveOutGetDevCapsA() { return reinterpret_cast<decltype(&waveOutGetDevCapsA)>(winmm_wave_out_get_dev_caps_a)(); }
DLL_EXPORT void waveOutGetDevCapsW() { return reinterpret_cast<decltype(&waveOutGetDevCapsW)>(winmm_wave_out_get_dev_caps_w)(); }
DLL_EXPORT void waveOutGetErrorTextA() { return reinterpret_cast<decltype(&waveOutGetErrorTextA)>(winmm_wave_out_get_error_text_a)(); }
DLL_EXPORT void waveOutGetErrorTextW() { return reinterpret_cast<decltype(&waveOutGetErrorTextW)>(winmm_wave_out_get_error_text_w)(); }
DLL_EXPORT void waveOutGetID() { return reinterpret_cast<decltype(&waveOutGetID)>(winmm_wave_out_get_id)(); }
DLL_EXPORT void waveOutGetNumDevs() { return reinterpret_cast<decltype(&waveOutGetNumDevs)>(winmm_wave_out_get_num_devs)(); }
DLL_EXPORT void waveOutGetPitch() { return reinterpret_cast<decltype(&waveOutGetPitch)>(winmm_wave_out_get_pitch)(); }
DLL_EXPORT void waveOutGetPlaybackRate() { return reinterpret_cast<decltype(&waveOutGetPlaybackRate)>(winmm_wave_out_get_playback_rate)(); }
DLL_EXPORT void waveOutGetPosition() { return reinterpret_cast<decltype(&waveOutGetPosition)>(winmm_wave_out_get_position)(); }
DLL_EXPORT void waveOutGetVolume() { return reinterpret_cast<decltype(&waveOutGetVolume)>(winmm_wave_out_get_volume)(); }
DLL_EXPORT void waveOutMessage() { return reinterpret_cast<decltype(&waveOutMessage)>(winmm_wave_out_message)(); }
DLL_EXPORT void waveOutOpen() { return reinterpret_cast<decltype(&waveOutOpen)>(winmm_wave_out_open)(); }
DLL_EXPORT void waveOutPause() { return reinterpret_cast<decltype(&waveOutPause)>(winmm_wave_out_pause)(); }
DLL_EXPORT void waveOutPrepareHeader() { return reinterpret_cast<decltype(&waveOutPrepareHeader)>(winmm_wave_out_prepare_header)(); }
DLL_EXPORT void waveOutReset() { return reinterpret_cast<decltype(&waveOutReset)>(winmm_wave_out_reset)(); }
DLL_EXPORT void waveOutRestart() { return reinterpret_cast<decltype(&waveOutRestart)>(winmm_wave_out_restart)(); }
DLL_EXPORT void waveOutSetPitch() { return reinterpret_cast<decltype(&waveOutSetPitch)>(winmm_wave_out_set_pitch)(); }
DLL_EXPORT void waveOutSetPlaybackRate() { return reinterpret_cast<decltype(&waveOutSetPlaybackRate)>(winmm_wave_out_set_playback_rate)(); }
DLL_EXPORT void waveOutSetVolume() { return reinterpret_cast<decltype(&waveOutSetVolume)>(winmm_wave_out_set_volume)(); }
DLL_EXPORT void waveOutUnprepareHeader() { return reinterpret_cast<decltype(&waveOutUnprepareHeader)>(winmm_wave_out_unprepare_header)(); }
DLL_EXPORT void waveOutWrite() { return reinterpret_cast<decltype(&waveOutWrite)>(winmm_wave_out_write)(); }
// clang-format on
// NOLINTEND(readability-identifier-naming, readability-avoid-return-with-void-value)

void init(HMODULE /*this_dll*/) {
    // Suspend all other threads to prevent a giant race condition
    const util::ThreadSuspender suspender{};

    wchar_t buf[MAX_PATH];
    if (GetSystemDirectoryW(&buf[0], ARRAYSIZE(buf)) == 0) {
        std::cerr << "Unable to find system dll directory! We're probably about to crash.\n";
        return;
    }

    auto system_winmm = std::filesystem::path{static_cast<wchar_t*>(buf)} / "winmm.dll";
    winmm_dll_handle = LoadLibraryA(system_winmm.generic_string().c_str());
    if (winmm_dll_handle == nullptr) {
        std::cerr << "Unable to find system winmm.dll! We're probably about to crash.\n";
        return;
    }

    winmm_close_driver = GetProcAddress(winmm_dll_handle, "CloseDriver");
    winmm_def_driver_proc = GetProcAddress(winmm_dll_handle, "DefDriverProc");
    winmm_driver_callback = GetProcAddress(winmm_dll_handle, "DriverCallback");
    winmm_drv_get_module_handle = GetProcAddress(winmm_dll_handle, "DrvGetModuleHandle");
    winmm_get_driver_module_handle = GetProcAddress(winmm_dll_handle, "GetDriverModuleHandle");
    winmm_open_driver = GetProcAddress(winmm_dll_handle, "OpenDriver");
    winmm_play_sound = GetProcAddress(winmm_dll_handle, "PlaySound");
    winmm_play_sound_a = GetProcAddress(winmm_dll_handle, "PlaySoundA");
    winmm_play_sound_w = GetProcAddress(winmm_dll_handle, "PlaySoundW");
    winmm_send_driver_message = GetProcAddress(winmm_dll_handle, "SendDriverMessage");
    winmm_wow_app_exit = GetProcAddress(winmm_dll_handle, "WOWAppExit");
    winmm_aux_get_dev_caps_a = GetProcAddress(winmm_dll_handle, "auxGetDevCapsA");
    winmm_aux_get_dev_caps_w = GetProcAddress(winmm_dll_handle, "auxGetDevCapsW");
    winmm_aux_get_num_devs = GetProcAddress(winmm_dll_handle, "auxGetNumDevs");
    winmm_aux_get_volume = GetProcAddress(winmm_dll_handle, "auxGetVolume");
    winmm_aux_out_message = GetProcAddress(winmm_dll_handle, "auxOutMessage");
    winmm_aux_set_volume = GetProcAddress(winmm_dll_handle, "auxSetVolume");
    winmm_joy_config_changed = GetProcAddress(winmm_dll_handle, "joyConfigChanged");
    winmm_joy_get_dev_caps_a = GetProcAddress(winmm_dll_handle, "joyGetDevCapsA");
    winmm_joy_get_dev_caps_w = GetProcAddress(winmm_dll_handle, "joyGetDevCapsW");
    winmm_joy_get_num_devs = GetProcAddress(winmm_dll_handle, "joyGetNumDevs");
    winmm_joy_get_pos = GetProcAddress(winmm_dll_handle, "joyGetPos");
    winmm_joy_get_pos_ex = GetProcAddress(winmm_dll_handle, "joyGetPosEx");
    winmm_joy_get_threshold = GetProcAddress(winmm_dll_handle, "joyGetThreshold");
    winmm_joy_release_capture = GetProcAddress(winmm_dll_handle, "joyReleaseCapture");
    winmm_joy_set_capture = GetProcAddress(winmm_dll_handle, "joySetCapture");
    winmm_joy_set_threshold = GetProcAddress(winmm_dll_handle, "joySetThreshold");
    winmm_mci_driver_notify = GetProcAddress(winmm_dll_handle, "mciDriverNotify");
    winmm_mci_driver_yield = GetProcAddress(winmm_dll_handle, "mciDriverYield");
    winmm_mci_execute = GetProcAddress(winmm_dll_handle, "mciExecute");
    winmm_mci_free_command_resource = GetProcAddress(winmm_dll_handle, "mciFreeCommandResource");
    winmm_mci_get_creator_task = GetProcAddress(winmm_dll_handle, "mciGetCreatorTask");
    winmm_mci_get_device_id_a = GetProcAddress(winmm_dll_handle, "mciGetDeviceIDA");
    winmm_mci_get_device_id_from_element_id_a =
        GetProcAddress(winmm_dll_handle, "mciGetDeviceIDFromElementIDA");
    winmm_mci_get_device_id_from_element_id_w =
        GetProcAddress(winmm_dll_handle, "mciGetDeviceIDFromElementIDW");
    winmm_mci_get_device_id_w = GetProcAddress(winmm_dll_handle, "mciGetDeviceIDW");
    winmm_mci_get_driver_data = GetProcAddress(winmm_dll_handle, "mciGetDriverData");
    winmm_mci_get_error_string_a = GetProcAddress(winmm_dll_handle, "mciGetErrorStringA");
    winmm_mci_get_error_string_w = GetProcAddress(winmm_dll_handle, "mciGetErrorStringW");
    winmm_mci_get_yield_proc = GetProcAddress(winmm_dll_handle, "mciGetYieldProc");
    winmm_mci_load_command_resource = GetProcAddress(winmm_dll_handle, "mciLoadCommandResource");
    winmm_mci_send_command_a = GetProcAddress(winmm_dll_handle, "mciSendCommandA");
    winmm_mci_send_command_w = GetProcAddress(winmm_dll_handle, "mciSendCommandW");
    winmm_mci_send_string_a = GetProcAddress(winmm_dll_handle, "mciSendStringA");
    winmm_mci_send_string_w = GetProcAddress(winmm_dll_handle, "mciSendStringW");
    winmm_mci_set_driver_data = GetProcAddress(winmm_dll_handle, "mciSetDriverData");
    winmm_mci_set_yield_proc = GetProcAddress(winmm_dll_handle, "mciSetYieldProc");
    winmm_midi_connect = GetProcAddress(winmm_dll_handle, "midiConnect");
    winmm_midi_disconnect = GetProcAddress(winmm_dll_handle, "midiDisconnect");
    winmm_midi_in_add_buffer = GetProcAddress(winmm_dll_handle, "midiInAddBuffer");
    winmm_midi_in_close = GetProcAddress(winmm_dll_handle, "midiInClose");
    winmm_midi_in_get_dev_caps_a = GetProcAddress(winmm_dll_handle, "midiInGetDevCapsA");
    winmm_midi_in_get_dev_caps_w = GetProcAddress(winmm_dll_handle, "midiInGetDevCapsW");
    winmm_midi_in_get_error_text_a = GetProcAddress(winmm_dll_handle, "midiInGetErrorTextA");
    winmm_midi_in_get_error_text_w = GetProcAddress(winmm_dll_handle, "midiInGetErrorTextW");
    winmm_midi_in_get_id = GetProcAddress(winmm_dll_handle, "midiInGetID");
    winmm_midi_in_get_num_devs = GetProcAddress(winmm_dll_handle, "midiInGetNumDevs");
    winmm_midi_in_message = GetProcAddress(winmm_dll_handle, "midiInMessage");
    winmm_midi_in_open = GetProcAddress(winmm_dll_handle, "midiInOpen");
    winmm_midi_in_prepare_header = GetProcAddress(winmm_dll_handle, "midiInPrepareHeader");
    winmm_midi_in_reset = GetProcAddress(winmm_dll_handle, "midiInReset");
    winmm_midi_in_start = GetProcAddress(winmm_dll_handle, "midiInStart");
    winmm_midi_in_stop = GetProcAddress(winmm_dll_handle, "midiInStop");
    winmm_midi_in_unprepare_header = GetProcAddress(winmm_dll_handle, "midiInUnprepareHeader");
    winmm_midi_out_cache_drum_patches = GetProcAddress(winmm_dll_handle, "midiOutCacheDrumPatches");
    winmm_midi_out_cache_patches = GetProcAddress(winmm_dll_handle, "midiOutCachePatches");
    winmm_midi_out_close = GetProcAddress(winmm_dll_handle, "midiOutClose");
    winmm_midi_out_get_dev_caps_a = GetProcAddress(winmm_dll_handle, "midiOutGetDevCapsA");
    winmm_midi_out_get_dev_caps_w = GetProcAddress(winmm_dll_handle, "midiOutGetDevCapsW");
    winmm_midi_out_get_error_text_a = GetProcAddress(winmm_dll_handle, "midiOutGetErrorTextA");
    winmm_midi_out_get_error_text_w = GetProcAddress(winmm_dll_handle, "midiOutGetErrorTextW");
    winmm_midi_out_get_id = GetProcAddress(winmm_dll_handle, "midiOutGetID");
    winmm_midi_out_get_num_devs = GetProcAddress(winmm_dll_handle, "midiOutGetNumDevs");
    winmm_midi_out_get_volume = GetProcAddress(winmm_dll_handle, "midiOutGetVolume");
    winmm_midi_out_long_msg = GetProcAddress(winmm_dll_handle, "midiOutLongMsg");
    winmm_midi_out_message = GetProcAddress(winmm_dll_handle, "midiOutMessage");
    winmm_midi_out_open = GetProcAddress(winmm_dll_handle, "midiOutOpen");
    winmm_midi_out_prepare_header = GetProcAddress(winmm_dll_handle, "midiOutPrepareHeader");
    winmm_midi_out_reset = GetProcAddress(winmm_dll_handle, "midiOutReset");
    winmm_midi_out_set_volume = GetProcAddress(winmm_dll_handle, "midiOutSetVolume");
    winmm_midi_out_short_msg = GetProcAddress(winmm_dll_handle, "midiOutShortMsg");
    winmm_midi_out_unprepare_header = GetProcAddress(winmm_dll_handle, "midiOutUnprepareHeader");
    winmm_midi_stream_close = GetProcAddress(winmm_dll_handle, "midiStreamClose");
    winmm_midi_stream_open = GetProcAddress(winmm_dll_handle, "midiStreamOpen");
    winmm_midi_stream_out = GetProcAddress(winmm_dll_handle, "midiStreamOut");
    winmm_midi_stream_pause = GetProcAddress(winmm_dll_handle, "midiStreamPause");
    winmm_midi_stream_position = GetProcAddress(winmm_dll_handle, "midiStreamPosition");
    winmm_midi_stream_property = GetProcAddress(winmm_dll_handle, "midiStreamProperty");
    winmm_midi_stream_restart = GetProcAddress(winmm_dll_handle, "midiStreamRestart");
    winmm_midi_stream_stop = GetProcAddress(winmm_dll_handle, "midiStreamStop");
    winmm_mixer_close = GetProcAddress(winmm_dll_handle, "mixerClose");
    winmm_mixer_get_control_details_a = GetProcAddress(winmm_dll_handle, "mixerGetControlDetailsA");
    winmm_mixer_get_control_details_w = GetProcAddress(winmm_dll_handle, "mixerGetControlDetailsW");
    winmm_mixer_get_dev_caps_a = GetProcAddress(winmm_dll_handle, "mixerGetDevCapsA");
    winmm_mixer_get_dev_caps_w = GetProcAddress(winmm_dll_handle, "mixerGetDevCapsW");
    winmm_mixer_get_id = GetProcAddress(winmm_dll_handle, "mixerGetID");
    winmm_mixer_get_line_controls_a = GetProcAddress(winmm_dll_handle, "mixerGetLineControlsA");
    winmm_mixer_get_line_controls_w = GetProcAddress(winmm_dll_handle, "mixerGetLineControlsW");
    winmm_mixer_get_line_info_a = GetProcAddress(winmm_dll_handle, "mixerGetLineInfoA");
    winmm_mixer_get_line_info_w = GetProcAddress(winmm_dll_handle, "mixerGetLineInfoW");
    winmm_mixer_get_num_devs = GetProcAddress(winmm_dll_handle, "mixerGetNumDevs");
    winmm_mixer_message = GetProcAddress(winmm_dll_handle, "mixerMessage");
    winmm_mixer_open = GetProcAddress(winmm_dll_handle, "mixerOpen");
    winmm_mixer_set_control_details = GetProcAddress(winmm_dll_handle, "mixerSetControlDetails");
    winmm_mm_drv_install = GetProcAddress(winmm_dll_handle, "mmDrvInstall");
    winmm_mm_get_current_task = GetProcAddress(winmm_dll_handle, "mmGetCurrentTask");
    winmm_mm_task_block = GetProcAddress(winmm_dll_handle, "mmTaskBlock");
    winmm_mm_task_create = GetProcAddress(winmm_dll_handle, "mmTaskCreate");
    winmm_mm_task_signal = GetProcAddress(winmm_dll_handle, "mmTaskSignal");
    winmm_mm_task_yield = GetProcAddress(winmm_dll_handle, "mmTaskYield");
    winmm_mmio_advance = GetProcAddress(winmm_dll_handle, "mmioAdvance");
    winmm_mmio_ascend = GetProcAddress(winmm_dll_handle, "mmioAscend");
    winmm_mmio_close = GetProcAddress(winmm_dll_handle, "mmioClose");
    winmm_mmio_create_chunk = GetProcAddress(winmm_dll_handle, "mmioCreateChunk");
    winmm_mmio_descend = GetProcAddress(winmm_dll_handle, "mmioDescend");
    winmm_mmio_flush = GetProcAddress(winmm_dll_handle, "mmioFlush");
    winmm_mmio_get_info = GetProcAddress(winmm_dll_handle, "mmioGetInfo");
    winmm_mmio_install_io_proc_a = GetProcAddress(winmm_dll_handle, "mmioInstallIOProcA");
    winmm_mmio_install_io_proc_w = GetProcAddress(winmm_dll_handle, "mmioInstallIOProcW");
    winmm_mmio_open_a = GetProcAddress(winmm_dll_handle, "mmioOpenA");
    winmm_mmio_open_w = GetProcAddress(winmm_dll_handle, "mmioOpenW");
    winmm_mmio_read = GetProcAddress(winmm_dll_handle, "mmioRead");
    winmm_mmio_rename_a = GetProcAddress(winmm_dll_handle, "mmioRenameA");
    winmm_mmio_rename_w = GetProcAddress(winmm_dll_handle, "mmioRenameW");
    winmm_mmio_seek = GetProcAddress(winmm_dll_handle, "mmioSeek");
    winmm_mmio_send_message = GetProcAddress(winmm_dll_handle, "mmioSendMessage");
    winmm_mmio_set_buffer = GetProcAddress(winmm_dll_handle, "mmioSetBuffer");
    winmm_mmio_set_info = GetProcAddress(winmm_dll_handle, "mmioSetInfo");
    winmm_mmio_string_to_fourcc_a = GetProcAddress(winmm_dll_handle, "mmioStringToFOURCCA");
    winmm_mmio_string_to_fourcc_w = GetProcAddress(winmm_dll_handle, "mmioStringToFOURCCW");
    winmm_mmio_write = GetProcAddress(winmm_dll_handle, "mmioWrite");
    winmm_mmsystem_get_version = GetProcAddress(winmm_dll_handle, "mmsystemGetVersion");
    winmm_snd_play_sound_a = GetProcAddress(winmm_dll_handle, "sndPlaySoundA");
    winmm_snd_play_sound_w = GetProcAddress(winmm_dll_handle, "sndPlaySoundW");
    winmm_time_begin_period = GetProcAddress(winmm_dll_handle, "timeBeginPeriod");
    winmm_time_end_period = GetProcAddress(winmm_dll_handle, "timeEndPeriod");
    winmm_time_get_dev_caps = GetProcAddress(winmm_dll_handle, "timeGetDevCaps");
    winmm_time_get_system_time = GetProcAddress(winmm_dll_handle, "timeGetSystemTime");
    winmm_time_get_time = GetProcAddress(winmm_dll_handle, "timeGetTime");
    winmm_time_kill_event = GetProcAddress(winmm_dll_handle, "timeKillEvent");
    winmm_time_set_event = GetProcAddress(winmm_dll_handle, "timeSetEvent");
    winmm_wave_in_add_buffer = GetProcAddress(winmm_dll_handle, "waveInAddBuffer");
    winmm_wave_in_close = GetProcAddress(winmm_dll_handle, "waveInClose");
    winmm_wave_in_get_dev_caps_a = GetProcAddress(winmm_dll_handle, "waveInGetDevCapsA");
    winmm_wave_in_get_dev_caps_w = GetProcAddress(winmm_dll_handle, "waveInGetDevCapsW");
    winmm_wave_in_get_error_text_a = GetProcAddress(winmm_dll_handle, "waveInGetErrorTextA");
    winmm_wave_in_get_error_text_w = GetProcAddress(winmm_dll_handle, "waveInGetErrorTextW");
    winmm_wave_in_get_id = GetProcAddress(winmm_dll_handle, "waveInGetID");
    winmm_wave_in_get_num_devs = GetProcAddress(winmm_dll_handle, "waveInGetNumDevs");
    winmm_wave_in_get_position = GetProcAddress(winmm_dll_handle, "waveInGetPosition");
    winmm_wave_in_message = GetProcAddress(winmm_dll_handle, "waveInMessage");
    winmm_wave_in_open = GetProcAddress(winmm_dll_handle, "waveInOpen");
    winmm_wave_in_prepare_header = GetProcAddress(winmm_dll_handle, "waveInPrepareHeader");
    winmm_wave_in_reset = GetProcAddress(winmm_dll_handle, "waveInReset");
    winmm_wave_in_start = GetProcAddress(winmm_dll_handle, "waveInStart");
    winmm_wave_in_stop = GetProcAddress(winmm_dll_handle, "waveInStop");
    winmm_wave_in_unprepare_header = GetProcAddress(winmm_dll_handle, "waveInUnprepareHeader");
    winmm_wave_out_break_loop = GetProcAddress(winmm_dll_handle, "waveOutBreakLoop");
    winmm_wave_out_close = GetProcAddress(winmm_dll_handle, "waveOutClose");
    winmm_wave_out_get_dev_caps_a = GetProcAddress(winmm_dll_handle, "waveOutGetDevCapsA");
    winmm_wave_out_get_dev_caps_w = GetProcAddress(winmm_dll_handle, "waveOutGetDevCapsW");
    winmm_wave_out_get_error_text_a = GetProcAddress(winmm_dll_handle, "waveOutGetErrorTextA");
    winmm_wave_out_get_error_text_w = GetProcAddress(winmm_dll_handle, "waveOutGetErrorTextW");
    winmm_wave_out_get_id = GetProcAddress(winmm_dll_handle, "waveOutGetID");
    winmm_wave_out_get_num_devs = GetProcAddress(winmm_dll_handle, "waveOutGetNumDevs");
    winmm_wave_out_get_pitch = GetProcAddress(winmm_dll_handle, "waveOutGetPitch");
    winmm_wave_out_get_playback_rate = GetProcAddress(winmm_dll_handle, "waveOutGetPlaybackRate");
    winmm_wave_out_get_position = GetProcAddress(winmm_dll_handle, "waveOutGetPosition");
    winmm_wave_out_get_volume = GetProcAddress(winmm_dll_handle, "waveOutGetVolume");
    winmm_wave_out_message = GetProcAddress(winmm_dll_handle, "waveOutMessage");
    winmm_wave_out_open = GetProcAddress(winmm_dll_handle, "waveOutOpen");
    winmm_wave_out_pause = GetProcAddress(winmm_dll_handle, "waveOutPause");
    winmm_wave_out_prepare_header = GetProcAddress(winmm_dll_handle, "waveOutPrepareHeader");
    winmm_wave_out_reset = GetProcAddress(winmm_dll_handle, "waveOutReset");
    winmm_wave_out_restart = GetProcAddress(winmm_dll_handle, "waveOutRestart");
    winmm_wave_out_set_pitch = GetProcAddress(winmm_dll_handle, "waveOutSetPitch");
    winmm_wave_out_set_playback_rate = GetProcAddress(winmm_dll_handle, "waveOutSetPlaybackRate");
    winmm_wave_out_set_volume = GetProcAddress(winmm_dll_handle, "waveOutSetVolume");
    winmm_wave_out_unprepare_header = GetProcAddress(winmm_dll_handle, "waveOutUnprepareHeader");
    winmm_wave_out_write = GetProcAddress(winmm_dll_handle, "waveOutWrite");
}

void free(void) {
    if (winmm_dll_handle != nullptr) {
        FreeLibrary(winmm_dll_handle);
        winmm_dll_handle = nullptr;
    }
}

}  // namespace pluginloader::proxy
