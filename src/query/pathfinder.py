#!/usr/bin/env python3
from csvql import Query
import libdijk
import sys
import time


def nodes_stops(sub):
    stops = Query('stops').as_gen()
    for s in stops:
        sid = s['stop_id']
        name = s['stop_name']
        sub.add_node(sid,name)
        # Necessary for switching platforms and maybe walking between other stations
        if 'parent_station' in s and s['parent_station']:
            sub.add_edge('Platform change',sid,s['parent_station'],0)
            sub.add_edge('Platform change',s['parent_station'],sid,0)

    return sub

def edges_transfers(sub):
    transfers = Query('transfers').as_gen()
    for tr in transfers:
        src = tr['from_stop_id']
        dest = tr['to_stop_id']
        metric = tr['min_transfer_time']
        sub.add_edge('Transfer',src,dest,int(metric))
    return sub

def tc_offset(time):
    h,m,s = [int(tc) for tc in time.split(':')]
    return h * 3600 + m * 60 + s    

def edges_stop_times(sub):
    stop_times = Query('stop_times').join('trips','trip_id').join('routes','route_id').as_gen()
    
    last_trip = None
    last_stop = None
    last_time = 0

    for st in stop_times:
        if st['trip_id'] != last_trip:
            last_trip = st['trip_id']
            last_stop = st['stop_id']
            last_time = tc_offset(st['arrival_time'])
            continue

        edge_label = '%s to %s' % (st['route_short_name'],st['trip_headsign'])
        sub.add_edge(edge_label,last_stop,st['stop_id'], tc_offset(st['arrival_time']) - last_time)
        last_stop = st['stop_id']
        last_time = tc_offset(st['arrival_time'])
    return sub

def build():
    print("Reading through stop_times.csv takes a long time.... please wait")
    sub = libdijk.Graph()
    t0 = time.time()
    sub = nodes_stops(sub)
    sub = edges_transfers(sub)
    sub = edges_stop_times(sub)
    t1 = time.time()
    print("Generating graph took %6.3f s" % (t1-t0))
    return sub


def print_path(path):
    for stn in path:
        print("%-32s\t%3d s\tvia\t%-32s" % (stn.node.name, stn.metric, stn.out_edge.name)) 

def search(src,dest):
    sub = build()
    t0 = time.time()
    src_graph = sub.path_from(src)
    t1 = time.time()
    print("Computing shortest paths from source took %6.3f s" % (t1-t0))
    print_path(src_graph.to(dest))
    t2 = time.time()
    print("Finding route to destination took %6.3f s" % (t2 - t1))

def main():
    if len(sys.argv) >= 3:
        search(sys.argv[1],sys.argv[2])
    else:
        raise TypeError

if __name__ == '__main__':
    main()
