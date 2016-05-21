/*
 * OpenslSink.h
 *
 * Created on: 2016��5��15��
 *     Author: loushuai
 */

#ifndef JNI_MEDIASINK_AUDIOSINK_OPENSL_OPENSLSINK_H_
#define JNI_MEDIASINK_AUDIOSINK_OPENSL_OPENSLSINK_H_

#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
#include <memory>
#include "../audiosink.hpp"

namespace bigbean
{

class OpenslSink : public AudioSink
{
public:
  OpenslSink();
  virtual ~OpenslSink();

  int open( uint32_t sampleRate, int channelCount,
            pcm_format_t format=PCM_FORMAT_FIXED_8,
            AudioCallback cb = NULL);

  int start();

private:
	/**
	 *  @brief ����opensl����
	 */
	int CreateEngine();

	/**
	 *  @brief ����audio player
	 */
	int createBufferQueueAudioPlayer(uint32_t sampleRate,
									 int channelCount,
									 pcm_format_t format);

	/**
	  * @brief  ��Ƶ���Żص�����
	  * @author  
	  * @param[in]	bq BufferQueue����ӿ�
	  * @param[in] context �ص���������ݣ�PCM����
	  * @return void
	*/
	static void AudioPlayerCallback(SLAndroidSimpleBufferQueueItf bq, void *context);

	/*
	 * @brief convert digital sample rate to opensl sample rate
	 */
	SLuint32 openslSampleRate(int32_t sr);

	/*
	 * @brief return opensl pcm format
	 */
	SLuint16 openslPcmFormat(pcm_format_t format);

  	/**
	  * @brief  ��Ƶ�����������
	*/
	SLObjectItf mEngineObject;
	/**
	  * @brief  ��Ƶ��������ӿ�
	*/
	SLEngineItf mEngine;
	/**
	  * @brief  ��Ƶ������������
	*/
	SLObjectItf mOutputMixObject;
	/**
	  * @brief  ��Ƶ���Ŷ���
	*/
	SLObjectItf mPlayerObject;
	/**
	  * @brief  ��Ƶ���Žӿ�
	*/
	SLPlayItf mPlayerPlay;
	/**
	  * @brief  BufferQueue����ӿ�
	*/
	SLAndroidSimpleBufferQueueItf mPlayerBufferQueue;
	/*
	 * @brief �����ӿ�
	 */
	SLVolumeItf mPlayerVolume;

	/*
	 *  @brief �������ص�
	 */
	AudioCallback mCallBack;

	/*
	 * @brief pcm buffer
	 */
	std::unique_ptr<uint8_t[]> mBuffer;
};
  
}

#endif /*JNI_MEDIASINK_AUDIOSINK_OPENSL_OPENSLSINK_H_*/
