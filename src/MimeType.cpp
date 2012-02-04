/****************************************************************************
* This file is part of xzHTTPd.                                             *
* Copyleft alkz                                                             *
*                                                                           *
* xzHTTPd is free software: you can redistribute it and/or modify           *
* it under the terms of the GNU General Public License as published by      *
* the Free Software Foundation, either version 3 of the License, or         *
* (at your option) any later version.                                       *
*                                                                           *
* xzHTTPd is distributed in the hope that it will be useful.                *
* but WITHOUT ANY WARRANTY; without even the implied warranty o.            *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See th.              *
* GNU General Public License for more details.                              *
*                                                                           *
* You should have received a copy of the GNU General Public License         *
* along with xzHTTPd. If not, see <http://www.gnu.org/licenses/>.           *
****************************************************************************/


#ifndef __XZHTTPD__MIMETYPE_CPP__
#define __XZHTTPD__MIMETYPE_CPP__ 


#include "MimeType.hpp"


namespace xzHTTPd  {


namespace Server  {


namespace MimeType  {


void
initMimes(void)
{
    if(inited)  {
        return;
    } else  {

        // Let's add default mimes

        mimes.insert( MimePair( "gif",   "image/gif"  ) );
        mimes.insert( MimePair( "jpg",   "image/jpeg" ) );
        mimes.insert( MimePair( "jpeg",  "image/jpeg" ) );
        mimes.insert( MimePair( "png",   "image/png"  ) );
        mimes.insert( MimePair( "zip",   "image/zip"  ) );
        mimes.insert( MimePair( "gz",    "image/gz"   ) );
        mimes.insert( MimePair( "tar",   "image/tar"  ) );
        mimes.insert( MimePair( "htm",   "text/html"  ) );
        mimes.insert( MimePair( "html",  "text/html"  ) );
        mimes.insert( MimePair( "css",   "text/css"   ) );

        inited = true;
    }
}


std::string
getMimeType(const std::string& ext)
{
    initMimes();

    std::size_t beginExt = ext.find_first_of(".", 1);
    std::string type = ext.substr(
                                  beginExt+1, 
                                  ext.find_first_of(
                                                      beginExt, 
                                                      ext.find_first_of(" ", beginExt) - beginExt
                                                   )
                               );
    
    MimeTable::const_iterator MI;
    for(MI = mimes.begin(); MI != mimes.end(); MI++)  {
        if(MI->first == type)  {
            break;
        }
    }

    if(MI->second == "")  {    // Let's find it in MimeTypes.conf
        std::cout << "mimePath: " << mimePath << std::endl;

        std::ifstream f;     f.open(mimePath, std::ios::ate);
        if(!f.is_open() || !f.tellg() )  {
            throw( Exception::Exception(Exception::Exception::MIME_OPEN_FILE) );
        }

//        unsigned char buffer[1024];
//        mimes.insert( MimePair( "css",   "text/css"   ) );

    } else  {
        return (MI->second);
    }

    return "";
}


/*
void
parseMimeFile(void)
{
}
*/



}


}


}


#endif
