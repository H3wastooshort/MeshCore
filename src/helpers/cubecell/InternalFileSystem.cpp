#include "InternalFileSystem.h"

static int _internal_flash_read(const struct lfs_config *c, lfs_block_t block, lfs_off_t off, void *buffer, lfs_size_t size) {
    auto addroffset = (block * c->block_size) + off;
    if(FLASH_read_at(EEPROM_BASE+addroffset, reinterpret_cast<uint8_t *>(buffer), size) == 0) return LFS_ERR_OK;
    return LFS_ERR_IO;
}
static int _internal_flash_prog(const struct lfs_config *c, lfs_block_t block, lfs_off_t off, const void *buffer, lfs_size_t size) {
    auto addroffset = (block * c->block_size) + off;
    if(FLASH_update(EEPROM_BASE+addroffset, reinterpret_cast<const void *>(buffer), size) == 0) return LFS_ERR_OK;
    return LFS_ERR_IO;
}
static int _internal_flash_erase(const struct lfs_config *c, lfs_block_t block) {
    void* dummy = malloc(EEPROM_PAGESIZE);
    memset(dummy,0xFF,EEPROM_PAGESIZE);
    for(size_t off = 0; off < c->block_size; off += EEPROM_PAGESIZE)
        if(FLASH_update(EEPROM_BASE+(block * c->block_size), reinterpret_cast<const void *>(dummy), EEPROM_PAGESIZE) == -1)
            {free(dummy); return LFS_ERR_IO;}
    free(dummy);
    return LFS_ERR_OK;
}
static int _internal_flash_sync(const struct lfs_config *c) {    
    return LFS_ERR_OK; // don't need sync
}

static struct lfs_config _InternalFSConfig = {
    .context = NULL, 
    .read = &_internal_flash_read,
    .prog = &_internal_flash_prog,
    .erase = &_internal_flash_erase,
    .sync = &_internal_flash_sync,
    .read_size = EEPROM_RWSIZE,
    .prog_size = EEPROM_RWSIZE,
    .block_size = (EEPROM_RWSIZE * (EEPROM_PAGESIZE/EEPROM_RWSIZE)),
    .block_count = EEPROM_SIZE / (EEPROM_PAGESIZE/EEPROM_RWSIZE),
    .lookahead = EEPROM_PAGESIZE
};

InternalFileSystem InternalFS;

//--------------------------------------------------------------------+
//
//--------------------------------------------------------------------+

InternalFileSystem::InternalFileSystem(void)
  : Adafruit_LittleFS(&_InternalFSConfig)
{

}

bool InternalFileSystem::begin(void)
{
  volatile bool format_fs;
  #ifdef FORMAT_FS
  format_fs = true;
  #else
  format_fs = false; // you can always use debugger to force formatting ;)
  #endif
  // failed to mount, erase all sector then format and mount again
  if ( format_fs || !Adafruit_LittleFS::begin() )
  {
    // lfs format
    this->format();
    // mount again if still failed, give up
    if ( !Adafruit_LittleFS::begin() ) return false;
  }

  return true;
}
