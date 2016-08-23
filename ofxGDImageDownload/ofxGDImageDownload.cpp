//
//  ofxGDImageDownload.cpp
//  googleDocsImage
//
//  Created by lolo on 8/22/16.
//  http://armdz.com
//

#include "ofxGDImageDownload.h"

//  Event
ofEvent <ofxGDImageDownloadEvent> ofxGDImageDownloadEvent::events;
//

ofxGDImageDownload::ofxGDImageDownload()
{

}

ofxGDImageDownload::~ofxGDImageDownload()
{
    
}

void    ofxGDImageDownload::setup(string    _key)
{
    
    api_key = _key;
    Poco::Net::HTTPSStreamFactory::registerFactory();
    Poco::Net::initializeSSL();
    Poco::Net::SSLManager::InvalidCertificateHandlerPtr ptrHandler ( new Poco::Net::AcceptCertificateHandler(false) );
    ssl_context = ( new Poco::Net::Context(Poco::Net::Context::CLIENT_USE, "") );
    Poco::Net::SSLManager::instance().initializeClient(0, ptrHandler, ssl_context);
    uri = Poco::URI("https://docs.google.com");
}

void    ofxGDImageDownload::download(ofImage    *_image,string _id)
{
    image = _image;
    current_image_id = _id;
    image_download_path = "";
    headers.clear();
    headers["Authorization"] = api_key;
    headers["Accept"] = "*/*";
    http_session = new Poco::Net::HTTPSClientSession(uri.getHost(), uri.getPort(), ssl_context);
    startThread();
}

void    ofxGDImageDownload::stop()
{
    stopThread();
}

void    ofxGDImageDownload::threadedFunction()
{
    while(isThreadRunning())
    {
        string  image_path = "/uc?id="+current_image_id+"&export=download";
        http_req = new Poco::Net::HTTPRequest(Poco::Net::HTTPRequest::HTTP_POST, image_path, Poco::Net::HTTPRequest::HTTP_1_1);
        http_req->setContentType("text/plain");
        http_req->setContentLength(0);
        for(map<string,string>::iterator it = headers.begin();
            it != headers.end(); it++) {
            http_req->set(it->first, it->second);
        }
        try
        {
            std::ostream& os = http_session->sendRequest(*http_req);
            
            Poco::Net::HTTPResponse res;
            istream& r = http_session->receiveResponse(res);
            ostringstream stream;
            Poco::StreamCopier::copyStream(r, stream);
            string response = stream.str();
            if(res.getStatus() == 200)
            {
                //  ok
                vector<string>  res_parts = ofSplitString(response, ",");
                res_parts = ofSplitString(res_parts.at(1), ":");
                image_download_path = "https:"+res_parts.at(2).substr(0,res_parts.at(2).size()-1);
                res_parts.clear();
                //  download
                download_image();
            }else if(res.getStatus() == 404)
            {
                dispatch_error_event("404 File Not Found");
            }else
            {
                dispatch_error_event(response);
            }
            stop();
        }
        catch (Poco::Exception& exc)
        {
            //  error
            dispatch_error_event(exc.message());
        }

    }
}

void    ofxGDImageDownload::dispatch_download_event(ofImage    _image)
{
    ofxGDImageDownloadEvent    event = ofxGDImageDownloadEvent();
    event.ok = true;
    ofNotifyEvent(ofxGDImageDownloadEvent::events,event);
}

void    ofxGDImageDownload::dispatch_error_event(string _message)
{
    ofxGDImageDownloadEvent    event = ofxGDImageDownloadEvent();
    event.ok = false;
    event.error = _message;
    ofNotifyEvent(ofxGDImageDownloadEvent::events,event);
}

void    ofxGDImageDownload::download_image()
{
    ofRegisterURLNotification(this);
    ofLoadURLAsync(image_download_path,"gd_image");
}

void    ofxGDImageDownload::urlResponse(ofHttpResponse & response)
{
    if(response.status==200 && response.request.name == "gd_image"){
        image->load(response.data);
    }
    ofUnregisterURLNotification(this);
}