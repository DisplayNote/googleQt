#pragma once
#include "google/endpoint/ApiUtil.h"
#include "google/endpoint/ApiClient.h"

#include "gdrive/about/AboutRoutes.h"
#include "gdrive/files/FilesRoutes.h"
#include "gdrive/permissions/PermissionsRoutes.h"
#include "gdrive/comments/CommentsRoutes.h"

namespace googleQt
{
    class Endpoint;
    
    class GdriveRoutes{ 
    public:

        GdriveRoutes(Endpoint*);
        Endpoint* endpoint() { return m_endpoint; }

        files::FilesRoutes* getFiles();
        about::AboutRoutes* getAbout();
        permissions::PermissionsRoutes* getPermissions();
        comments::CommentsRoutes* getComments();

        class FolderContentMap 
        {
        public:
            std::map<QString, QString> id2name;
            std::map<QString, QString> name2id;
        };

        ///reserved folder for app-settings&files
        static QString appDataFolder();
        /// returns file ID if file exist, empty string otherwise
        QString  fileExists(QString name, QString parentFolderId = "");
        /// returns folder ID if folder exist, empty string otherwise
        QString  folderExists(QString name, QString parentFolderId = "");
        /// returns folder ID if folder was created, empty string otherwise
        QString  createFolder(QString name, QString parentFolderId = "");
        /// create a new folder if it doesn't exists, returns folder ID
        QString ensureFolder(QString name, QString parentFolderId = "");
        /// download file by ID
        bool downloadFileByID(QString fileId, QString localDestinationPath);
        /// download file by path, parentFolderId can be empty
        bool downloadFileByName(QString name, QString parentFolderId, QString localDestinationPath);
        /// delete existing file by ID
        bool deleteFile(QString fileID);
        /// rename existing file
        bool renameFile(QString fileID, QString newName);
        /// move file by ID from list of parent to new parents
        bool moveFile(QString fileID, const std::list<QString>& removeParentFolderIDs, const std::list<QString>& addParentFolderIDs);
        /// move file by ID from one parent to another
        bool moveFile(QString fileID, QString removeParentFolderID, QString addParentFolderID);
        /// upload file, delete existing, return ID of the new file
        QString uploadFile(QString localFilePath, QString destFileName, QString parentFolderId = "", QString mimeType = "");
        /// upload file into tmp and if succeeded replace existing file on cloud
        /// this prevent data tranfer errors, alows file validation etc.
        QString upgradeFile(QString localFilePath, QString destFileName, QString parentFolderId = "");
        /// returns name->folderid map for a parent folder
        FolderContentMap mapFolders(QString parentFolderId);
        /// returns name->fileid map for a parent folder
        FolderContentMap mapNonFolders(QString parentFolderId);
        /// returns name->fileid map for a parent folder using query parameter
        FolderContentMap mapFolderContent(QString parentFolderId, QString q = "trashed = false");

#ifdef API_QT_AUTOTEST
        void autotest() {};
#endif
    protected:
        std::unique_ptr<files::FilesRoutes> m_Files;
        std::unique_ptr<about::AboutRoutes> m_About;
        std::unique_ptr<permissions::PermissionsRoutes> m_Permissions;
        std::unique_ptr<comments::CommentsRoutes> m_Comments;
        Endpoint*  m_endpoint;
    };
};//googleQt
