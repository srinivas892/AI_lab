run :-
       title(_Heading),
       check(Tree),
       write('Upon checking those characteristics, the expert system deduced that tree might be: '),
       write(Tree), nl, undo.

 /* Trees to be checked */
check(treeferns) :- treeferns, !.
check(horsetails) :- horsetails, !.
check(clubmosses) :- clubmosses, !.
check(rice) :- rice, !.
check(corn) :- corn, !.
check(bananas) :- bananas, !.
check(tomato) :- tomato, !.
check(coffee) :- coffee, !.
check(cotton) :- cotton, !.
check(cyads) :- cyads, !.
check(gingko) :- gingko, !.
check(conifers) :- conifers, !.
check(unknown). /* no diagnosis */

/* Tree identification rules */
treeferns :- pteridophytes,
                    confirm(climate: humid_forests),
                    confirm(leaf_type: lacy_leaves),
                    confirm(height_10_to_7_meters).
horsetails :- pteridophytes,
               confirm(climate: watterlogged_areas),
               confirm(leaf_type: flowerless_tiny_leaves),
               confirm(height_1_to_2_ft).
clubmosses :- pteridophytes,
                    confirm(climate_moist_surroundings),
                    confirm(leaf_type_needlelike_leaves),
                    confirm(height_20_cm).
rice :- monocotyledonous,
             confirm(climate_tropics),
             confirm(leaf_type_long_slender_leaves),
             confirm(height_1_point_8_m).
corn :- monocotyledonous,
                   confirm(climate_warm_weather),
                   confirm(leaf_type_broad_leaf),
                   confirm(height_12_ft).
bananas :- monocotyledonous,
              confirm(climate_tropical_or_warm_subtropical),
              confirm(leaf_type_spiked_edges),
              confirm(height_16_ft).
tomato :- dicotyledonous,
                  confirm(climate_sunny_climate),
                  confirm(leaf_type_compound_leaves),
                  confirm(height_3_to_5_ft).
coffee :- dicotyledonous,
              confirm(climate_warm_tropical_climate),
              confirm(leaf_type_smooth_margin),
              confirm(height_3_to_3_point_5_m).
cotton :- dicotyledonous,
                   confirm(climate_tropical_subtropical_areas),
                   confirm(leaf_type_spirally_arranged),
                   confirm(height_6_ft).
cyads :- gymnosperms,
              confirm(climate_tropical_regions),
              confirm(leaf_type_sporophyll_leaves),
              confirm(height_20_m).
gingko :- gymnosperms,
                 confirm(climate_moderate_rainfall),
                 confirm(leaf_type_fan_shaped),
                 confirm(height_30_cm_per_year_first_30yrs_to_height_120_ft).
conifers :- gymnosperms,
              confirm(climate_northern_hemisphere),
              confirm(leaf_type_needlelike_leaves),
              confirm(height_60_to_100_ft).
/* classification rules */
pteridophytes :- confirm(seedless_plants).

gymnosperms :- confirm(produce_seeds).


angiosperms :- confirm(flowering_plants).


monocotyledonous :- angiosperms, confirm(has_one_cotyledon), !.
dicotyledonous :- angiosperms, confirm(has_two_cotyledons).
/* Dialogue with user where the answer is stored in asserta,z*/
title(_Heading) :-
               write('*** PHYLOGENETICS TREE EXPERT SYSTEMS ***'),nl.
ask(Question) :-
        write('Is this one of the characteristics of the tree? '),
        write(Question), write('? '),
         read(Response), nl,
         ( (Response == yes ; Response == y)
         -> asserta(yes(Question)) ;
         assertz(no(Question)), fail).

/* caching result */
:- dynamic([yes/1,no/1]).
/* How to confirm something */
confirm(S) :- (yes(S) -> true ; (no(S) -> fail ; ask(S))).
/* undo all yes or no assertions after we no longer need them */
undo :- retract(yes(_)),fail.
undo :- retract(no(_)),fail.
undo.









