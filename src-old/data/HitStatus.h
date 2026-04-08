#ifndef HIT_STATUS_H
#define HIT_STATUS_H

/**
 * Simple enum representing if a struck position 
 * hit or missed an opponent ship. "NONE" is a 
 * standin for null, and should never be returned 
 * after a strike.
 */
enum HitStatus {
    NONE,
    HIT,
    MISS
};

#endif