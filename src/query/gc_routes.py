#!/usr/bin/env python3
from csvql import Query

gc_stops = Query('stops').eq('stop_name','Grand Central - 42 St').get('stop_id').as_set()
gc_routes = Query('stop_times').ins('stop_id', gc_stops) \
    .join('trips','trip_id').join('routes','route_id') \
    .get('route_id').distinct().as_gen()

for route in gc_routes:
    print(route)
