/**
 * Created 190510 lynnl
 *
 * Taken from kernel header <sys/mount.h>
 * Kernel `struct vfs_attr', `VFSATTR_*' isn't export to user space in newer systems
 *
 */


/*
 * Kernel level support for the VFS_GETATTR(), VFS_SETATTR() for use in
 * implementation of filesystem KEXTs, and by the vfs_getattr() and
 * vfs_setattr() KPIs.
 */

#define VFSATTR_INIT(s)            ((s)->f_supported = (s)->f_active = 0LL)
#define VFSATTR_SET_SUPPORTED(s, a)    ((s)->f_supported |= VFSATTR_ ## a)
#define VFSATTR_IS_SUPPORTED(s, a)    ((s)->f_supported & VFSATTR_ ## a)
#define VFSATTR_CLEAR_ACTIVE(s, a)    ((s)->f_active &= ~VFSATTR_ ## a)
#define VFSATTR_IS_ACTIVE(s, a)        ((s)->f_active & VFSATTR_ ## a)
#define VFSATTR_ALL_SUPPORTED(s)    (((s)->f_active & (s)->f_supported) == (s)->f_active)
#define VFSATTR_WANTED(s, a)        ((s)->f_active |= VFSATTR_ ## a)
#define VFSATTR_RETURN(s, a, x)        do { (s)-> a = (x); VFSATTR_SET_SUPPORTED(s, a);} while(0)

#define VFSATTR_f_objcount        (1LL<<  0)
#define VFSATTR_f_filecount        (1LL<<  1)
#define VFSATTR_f_dircount        (1LL<<  2)
#define VFSATTR_f_maxobjcount        (1LL<<  3)
#define VFSATTR_f_bsize            (1LL<< 4)
#define VFSATTR_f_iosize        (1LL<<  5)
#define VFSATTR_f_blocks        (1LL<<  6)
#define VFSATTR_f_bfree            (1LL<<  7)
#define VFSATTR_f_bavail        (1LL<<  8)
#define VFSATTR_f_bused            (1LL<<  9)
#define VFSATTR_f_files            (1LL<< 10)
#define VFSATTR_f_ffree            (1LL<< 11)
#define VFSATTR_f_fsid            (1LL<< 12)
#define VFSATTR_f_owner            (1LL<< 13)
#define VFSATTR_f_capabilities        (1LL<< 14)
#define VFSATTR_f_attributes        (1LL<< 15)
#define VFSATTR_f_create_time        (1LL<< 16)
#define VFSATTR_f_modify_time        (1LL<< 17)
#define VFSATTR_f_access_time        (1LL<< 18)
#define VFSATTR_f_backup_time        (1LL<< 19)
#define VFSATTR_f_fssubtype        (1LL<< 20)
#define VFSATTR_f_vol_name        (1LL<< 21)
#define VFSATTR_f_signature        (1LL<< 22)
#define VFSATTR_f_carbon_fsid        (1LL<< 23)
#define VFSATTR_f_uuid            (1LL<< 24)
#define VFSATTR_f_quota        (1LL<< 25)
#define VFSATTR_f_reserved        (1LL<< 26)

typedef    unsigned char uuid_t[16];

/*
 * Argument structure.
 */
#pragma pack(4)
/*
 * Note: the size of the vfs_attr structure can change.
 * A kext should only reference the fields that are
 * marked as active; it should not depend on the actual
 * size of the structure or attempt to copy it.
 */
struct vfs_attr {
    uint64_t    f_supported;
    uint64_t    f_active;

    uint64_t    f_objcount;    /* number of filesystem objects in volume */
    uint64_t    f_filecount;    /* ... files */
    uint64_t    f_dircount;    /* ... directories */
    uint64_t    f_maxobjcount;    /* maximum number of filesystem objects */

    uint32_t    f_bsize;    /* block size for the below size values */
    size_t        f_iosize;    /* optimal transfer block size */
    uint64_t    f_blocks;    /* total data blocks in file system */
    uint64_t    f_bfree;    /* free blocks in fs */
    uint64_t    f_bavail;    /* free blocks avail to non-superuser */
    uint64_t    f_bused;    /* blocks in use */
    uint64_t    f_files;    /* total file nodes in file system */
    uint64_t    f_ffree;    /* free file nodes in fs */
    fsid_t        f_fsid;        /* file system id */
    uid_t        f_owner;    /* user that mounted the filesystem */

     vol_capabilities_attr_t f_capabilities;
    vol_attributes_attr_t f_attributes;

    struct timespec    f_create_time;    /* creation time */
    struct timespec    f_modify_time;    /* last modification time */
    struct timespec f_access_time;    /* time of last access */
    struct timespec    f_backup_time;    /* last backup time */

    uint32_t    f_fssubtype;    /* filesystem subtype */

    char        *f_vol_name;    /* volume name */

    uint16_t    f_signature;    /* used for ATTR_VOL_SIGNATURE, Carbon's FSVolumeInfo.signature */
    uint16_t    f_carbon_fsid;    /* same as Carbon's FSVolumeInfo.filesystemID */
    uuid_t        f_uuid;        /* file system UUID (version 3 or 5), available in 10.6 and later */
    uint64_t    f_quota;    /* total quota data blocks in file system */
    uint64_t    f_reserved;    /* total reserved data blocks in file system */
};

