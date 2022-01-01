/*
 * This file Copyright (C) 2005-2014 Mnemosyne LLC
 *
 * It may be used under the GNU GPL versions 2 or 3
 * or any future license endorsed by Mnemosyne LLC.
 *
 */

#pragma once

#include <ctime>
#include <string>
#include <string_view>
#include <vector>

#include "transmission.h"

#include "block-info.h"
#include "magnet-metainfo.h"
#include "quark.h"

struct tr_error;
struct tr_info;

struct tr_torrent_metainfo : public tr_magnet_metainfo
{
public:
    tr_torrent_metainfo() = default;
    ~tr_torrent_metainfo() override = default;

    [[nodiscard]] auto empty() const
    {
        return std::empty(files_);
    }

    bool parseBenc(std::string_view benc, tr_error** error = nullptr);

    // Helper function wrapper around parseBenc().
    // If you're looping through several files, passing in a non-nullptr
    // `buffer` can reduce the number of memory allocations needed to
    // load multiple files.
    bool parseTorrentFile(std::string_view benc_filename, std::vector<char>* buffer = nullptr, tr_error** error = nullptr);

    auto const& blockInfo() const
    {
        return block_info_;
    }
    auto pieceCount() const
    {
        return block_info_.n_pieces;
    }
    auto pieceSize() const
    {
        return block_info_.piece_size;
    }
    auto totalSize() const
    {
        return block_info_.total_size;
    }
    auto const& comment() const
    {
        return comment_;
    }

    auto const& creator() const
    {
        return creator_;
    }

    auto const& files() const
    {
        return files_;
    }

    [[nodiscard]] auto const& isPrivate() const
    {
        return is_private_;
    }

    [[nodiscard]] auto const& parsedTorrentFile() const
    {
        return torrent_file_;
    }

    [[nodiscard]] tr_sha1_digest_t const& pieceHash(tr_piece_index_t piece) const;

    [[nodiscard]] auto const& source() const
    {
        return source_;
    }

    [[nodiscard]] auto const& dateCreated() const
    {
        return date_created_;
    }

    void clear() final;

    [[nodiscard]] std::string benc() const;

    [[nodiscard]] auto infoDictSize() const
    {
        return info_dict_size_;
    }

    [[nodiscard]] auto infoDictOffset() const
    {
        return info_dict_offset_;
    }

private:
    static std::string parsePath(std::string_view root, tr_variant* path, std::string& buf);
    static std::string fixWebseedUrl(tr_torrent_metainfo const& tm, std::string_view url);
    static std::string_view parseFiles(tr_torrent_metainfo& setme, tr_variant* info_dict, uint64_t* setme_total_size);
    static std::string_view parseImpl(tr_torrent_metainfo& setme, tr_variant* meta, std::string_view benc);
    static std::string_view parseAnnounce(tr_torrent_metainfo& setme, tr_variant* meta);
    static void parseWebseeds(tr_torrent_metainfo& setme, tr_variant* meta);

    struct file_t
    {
    public:
        std::string const& path() const
        {
            return path_;
        }
        uint64_t length() const
        {
            return length_;
        }

        file_t(std::string_view path, uint64_t length)
            : path_{ path }
            , length_{ length }
        {
        }

    private:
        std::string path_;
        uint64_t length_ = 0;
    };

    tr_block_info block_info_ = tr_block_info{ 0, 0 };

    std::vector<tr_sha1_digest_t> pieces_;
    std::vector<file_t> files_;

    std::string comment_;
    std::string creator_;
    std::string source_;

    // empty unless `parseTorrentFile()` was used
    std::string torrent_file_;

    time_t date_created_ = 0;

    // Offset + size of the bencoded info dict subset of the bencoded data.
    // Used when loading pieces of it to sent to magnet peers.
    // See http://bittorrent.org/beps/bep_0009.html
    uint64_t info_dict_size_ = 0;
    uint64_t info_dict_offset_ = 0;

    // Offset of the bencoded 'pieces' checksums subset of the bencoded data.
    // Used when loading piece checksums on demand.
    uint64_t pieces_offset_ = 0;

    bool is_private_ = false;
};