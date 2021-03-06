/******************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  Logger Plugin
 * Author:   Joseph Curtis
 *
 ***************************************************************************
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************
 */

#ifndef _LOGGERPI_H_
#define _LOGGERPI_H_

#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
#include "wx/wx.h"
#endif //precompiled headers

#define PLUGIN_VERSION_MAJOR    0
#define PLUGIN_VERSION_MINOR    2

//#define MY_API_VERSION_MAJOR    1
//#define MY_API_VERSION_MINOR    2

#include <wx/fileconf.h>
#include "ocpn_plugin.h"

#define COMBINED_LOGFILE_FULL_PATH_DEFAULT "%Y-%m-%d.nmea"
#define GPS_LOGFILE_FULL_PATH_DEFAULT "gps.%Y-%m-%d.nmea"
#define AIS_LOGFILE_FULL_PATH_DEFAULT "ais.%Y-%m-%d.nmea"

#define GPS_LOG_ENABLED_DEFAULT TRUE
#define AIS_LOG_ENABLED_DEFAULT TRUE
#define COMBINED_LOG_ENABLED_DEFAULT FALSE

enum NMEASentenceType {
  GPS,
  AIS,
  UNKNOWN
};

class ConfigDialogImpl;

//----------------------------------------------------------------------------------------------------------
//    The PlugIn Class Definition
//----------------------------------------------------------------------------------------------------------

class logger_pi : public opencpn_plugin {
 public:
 logger_pi(void *ppimgr):opencpn_plugin(ppimgr){}
  
  //    The required PlugIn Methods
  int Init(void);
  bool DeInit(void);
  
  int GetAPIVersionMajor();
  int GetAPIVersionMinor();
  int GetPlugInVersionMajor();
  int GetPlugInVersionMinor();
  
  wxString GetCommonName();
  wxString GetShortDescription();
  wxString GetLongDescription();
  
  bool LoadConfig(void);
  bool SaveConfig(void);
  
  //    The optional method overrides
  
  void SetNMEASentence(wxString &sentence);
  void OnContextMenuItemCallback(int id);
  
  wxString combinedLogfileFullPath;
  wxString gpsLogfileFullPath;
  wxString aisLogfileFullPath;
  
  bool combinedLogEnabled;
  bool gpsLogEnabled;
  bool aisLogEnabled;
  
 private:
  wxWindow *m_parent_window;
  wxFileConfig *m_pconfig;
  ConfigDialogImpl *m_config_dialog;
  
  int m_show_id;
  int m_hide_id;
  
  NMEASentenceType determineNMEASentenceType(wxString sentence);
  void appendSentenceToFile(wxString fileFullPath, wxString sentence);
};

#endif



