#include "FigureAction_private.h"

#include "Calc.h"
#include "Figure.h"
#include "Routing.h"
#include "Security.h"
#include "Sound.h"
#include "Terrain.h"

#include "Data/CityInfo.h"
#include "Data/Formation.h"
#include "Data/Grid.h"

void FigureAction_taxCollector(int walkerId)
{
	struct Data_Walker *f = &Data_Walkers[walkerId];
	struct Data_Building *b = &Data_Buildings[f->buildingId];
	
	f->terrainUsage = FigureTerrainUsage_Roads;
	f->useCrossCountry = 0;
	f->maxRoamLength = 512;
	if (!BuildingIsInUse(f->buildingId) || b->figureId != walkerId) {
		f->state = FigureState_Dead;
	}
	FigureActionIncreaseGraphicOffset(f, 12);
	
	switch (f->actionState) {
		case FigureActionState_150_Attack:
			FigureAction_Common_handleAttack(walkerId);
			break;
		case FigureActionState_149_Corpse:
			FigureAction_Common_handleCorpse(walkerId);
			break;
		case FigureActionState_40_TaxCollectorCreated:
			f->isGhost = 1;
			f->graphicOffset = 0;
			f->waitTicks--;
			if (f->waitTicks <= 0) {
				int xRoad, yRoad;
				if (Terrain_getClosestRoadWithinRadius(b->x, b->y, b->size, 2, &xRoad, &yRoad)) {
					f->actionState = FigureActionState_41_TaxCollectorEnteringExiting;
					FigureAction_Common_setCrossCountryDestination(walkerId, f, xRoad, yRoad);
					f->roamLength = 0;
				} else {
					f->state = FigureState_Dead;
				}
			}
			break;
		case FigureActionState_41_TaxCollectorEnteringExiting:
			f->useCrossCountry = 1;
			f->isGhost = 1;
			if (FigureMovement_crossCountryWalkTicks(walkerId, 1) == 1) {
				if (Data_Grid_buildingIds[f->gridOffset] == f->buildingId) {
					// returned to own building
					f->state = FigureState_Dead;
				} else {
					f->actionState = FigureActionState_42_TaxCollectorRoaming;
					FigureMovement_initRoaming(walkerId);
					f->roamLength = 0;
				}
			}
			break;
		case FigureActionState_42_TaxCollectorRoaming:
			f->isGhost = 0;
			f->roamLength++;
			if (f->roamLength >= f->maxRoamLength) {
				int xRoad, yRoad;
				if (Terrain_getClosestRoadWithinRadius(b->x, b->y, b->size, 2, &xRoad, &yRoad)) {
					f->actionState = FigureActionState_43_TaxCollectorReturning;
					f->destinationX = xRoad;
					f->destinationY = yRoad;
				} else {
					f->state = FigureState_Dead;
				}
			}
			FigureMovement_roamTicks(walkerId, 1);
			break;
		case FigureActionState_43_TaxCollectorReturning:
			FigureMovement_walkTicks(walkerId, 1);
			if (f->direction == DirFigure_8_AtDestination) {
				f->actionState = FigureActionState_41_TaxCollectorEnteringExiting;
				FigureAction_Common_setCrossCountryDestination(walkerId, f, b->x, b->y);
				f->roamLength = 0;
			} else if (f->direction == DirFigure_9_Reroute || f->direction == DirFigure_10_Lost) {
				f->state = FigureState_Dead;
			}
			break;
	}
	WalkerActionUpdateGraphic(f, GraphicId(ID_Graphic_Figure_TaxCollector));
}

void FigureAction_engineer(int walkerId)
{
	struct Data_Walker *f = &Data_Walkers[walkerId];
	struct Data_Building *b = &Data_Buildings[f->buildingId];
	
	f->terrainUsage = FigureTerrainUsage_Roads;
	f->useCrossCountry = 0;
	f->maxRoamLength = 640;
	if (!BuildingIsInUse(f->buildingId) || b->figureId != walkerId) {
		f->state = FigureState_Dead;
	}
	FigureActionIncreaseGraphicOffset(f, 12);
	
	switch (f->actionState) {
		case FigureActionState_150_Attack:
			FigureAction_Common_handleAttack(walkerId);
			break;
		case FigureActionState_149_Corpse:
			FigureAction_Common_handleCorpse(walkerId);
			break;
		case FigureActionState_60_EngineerCreated:
			f->isGhost = 1;
			f->graphicOffset = 0;
			f->waitTicks--;
			if (f->waitTicks <= 0) {
				int xRoad, yRoad;
				if (Terrain_getClosestRoadWithinRadius(b->x, b->y, b->size, 2, &xRoad, &yRoad)) {
					f->actionState = FigureActionState_61_EngineerEnteringExiting;
					FigureAction_Common_setCrossCountryDestination(walkerId, f, xRoad, yRoad);
					f->roamLength = 0;
				} else {
					f->state = FigureState_Dead;
				}
			}
			break;
		case FigureActionState_61_EngineerEnteringExiting:
			f->useCrossCountry = 1;
			f->isGhost = 1;
			if (FigureMovement_crossCountryWalkTicks(walkerId, 1) == 1) {
				if (Data_Grid_buildingIds[f->gridOffset] == f->buildingId) {
					// returned to own building
					f->state = FigureState_Dead;
				} else {
					f->actionState = FigureActionState_62_EngineerRoaming;
					FigureMovement_initRoaming(walkerId);
					f->roamLength = 0;
				}
			}
			break;
		case FigureActionState_62_EngineerRoaming:
			f->isGhost = 0;
			f->roamLength++;
			if (f->roamLength >= f->maxRoamLength) {
				int xRoad, yRoad;
				if (Terrain_getClosestRoadWithinRadius(b->x, b->y, b->size, 2, &xRoad, &yRoad)) {
					f->actionState = FigureActionState_63_EngineerReturning;
					f->destinationX = xRoad;
					f->destinationY = yRoad;
				} else {
					f->state = FigureState_Dead;
				}
			}
			FigureMovement_roamTicks(walkerId, 1);
			break;
		case FigureActionState_63_EngineerReturning:
			FigureMovement_walkTicks(walkerId, 1);
			if (f->direction == DirFigure_8_AtDestination) {
				f->actionState = FigureActionState_61_EngineerEnteringExiting;
				FigureAction_Common_setCrossCountryDestination(walkerId, f, b->x, b->y);
				f->roamLength = 0;
			} else if (f->direction == DirFigure_9_Reroute || f->direction == DirFigure_10_Lost) {
				f->state = FigureState_Dead;
			}
			break;
	}
	WalkerActionUpdateGraphic(f, GraphicId(ID_Graphic_Figure_Engineer));
}

static int prefectGetNearestEnemy(int x, int y, int *distance)
{
	int minEnemyId = 0;
	int minDist = 10000;
	for (int i = 1; i < MAX_FIGURES; i++) {
		struct Data_Walker *f = &Data_Walkers[i];
		if (f->state != FigureState_Alive || f->targetedByFigureId) {
			continue;
		}
		int dist;
		if (f->type == Figure_Rioter || f->type == Figure_Enemy54_Gladiator) {
			dist = Calc_distanceMaximum(x, y, f->x, f->y);
		} else if (f->type == Figure_IndigenousNative && f->actionState == FigureActionState_159_NativeAttacking) {
			dist = Calc_distanceMaximum(x, y, f->x, f->y);
		} else if (FigureIsEnemy(f->type)) {
			dist = 3 * Calc_distanceMaximum(x, y, f->x, f->y);
		} else if (f->type == Figure_Wolf) {
			dist = 4 * Calc_distanceMaximum(x, y, f->x, f->y);
		} else {
			continue;
		}
		if (dist < minDist) {
			minDist = dist;
			minEnemyId = i;
		}
	}
	*distance = minDist;
	return minEnemyId;
}

static int prefectGoFightEnemy(int walkerId, struct Data_Walker *f)
{
	if (Data_CityInfo.riotersOrAttackingNativesInCity <= 0 && Data_Formation_Extra.numEnemyFormations <= 0) {
		return 0;
	}
	switch (f->actionState) {
		case FigureActionState_150_Attack:
		case FigureActionState_149_Corpse:
		case FigureActionState_70_PrefectCreated:
		case FigureActionState_71_PrefectEnteringExiting:
		case FigureActionState_74_PrefectGoingToFire:
		case FigureActionState_75_PrefectAtFire:
		case FigureActionState_76_PrefectGoingToEnemy:
		case FigureActionState_77_PrefectAtEnemy:
			return 0;
	}
	f->waitTicksNextTarget++;
	if (f->waitTicksNextTarget < 10) {
		return 0;
	}
	f->waitTicksNextTarget = 0;
	int distance;
	int enemyId = prefectGetNearestEnemy(f->x, f->y, &distance);
	if (enemyId > 0 && distance <= 30) {
		f->waitTicksNextTarget = 0;
		f->actionState = FigureActionState_76_PrefectGoingToEnemy;
		f->destinationX = Data_Walkers[enemyId].x;
		f->destinationY = Data_Walkers[enemyId].y;
		f->targetFigureId = enemyId;
		Data_Walkers[enemyId].targetedByFigureId = walkerId;
		f->targetFigureCreatedSequence = Data_Walkers[enemyId].createdSequence;
		FigureRoute_remove(walkerId);
		return 1;
	}
	return 0;
}

static int prefectGoFightFire(int walkerId, struct Data_Walker *f)
{
	if (Data_BuildingList.burning.size <= 0) {
		return 0;
	}
	switch (f->actionState) {
		case FigureActionState_150_Attack:
		case FigureActionState_149_Corpse:
		case FigureActionState_70_PrefectCreated:
		case FigureActionState_71_PrefectEnteringExiting:
		case FigureActionState_74_PrefectGoingToFire:
		case FigureActionState_75_PrefectAtFire:
		case FigureActionState_76_PrefectGoingToEnemy:
		case FigureActionState_77_PrefectAtEnemy:
			return 0;
	}
	f->waitTicksMissile++;
	if (f->waitTicksMissile < 20) {
		return 0;
	}
	int distance;
	int ruinId = Security_Fire_getClosestBurningRuin(f->x, f->y, &distance);
	if (ruinId > 0 && distance <= 25) {
		f->waitTicksMissile = 0;
		f->actionState = FigureActionState_74_PrefectGoingToFire;
		f->destinationX = Data_Buildings[ruinId].roadAccessX;
		f->destinationY = Data_Buildings[ruinId].roadAccessY;
		f->destinationBuildingId = ruinId;
		FigureRoute_remove(walkerId);
		Data_Buildings[ruinId].figureId4 = walkerId;
		return 1;
	}
	return 0;
}

static void prefectExtinguishFire(int walkerId, struct Data_Walker *f)
{
	struct Data_Building *burn = &Data_Buildings[f->destinationBuildingId];
	int distance = Calc_distanceMaximum(f->x, f->y, burn->x, burn->y);
	if (BuildingIsInUse(f->destinationBuildingId) && burn->type == Building_BurningRuin && distance < 2) {
		burn->fireDuration = 32;
		Sound_Effects_playChannel(SoundChannel_FireSplash);
	} else {
		f->waitTicks = 1;
	}
	f->attackDirection = Routing_getGeneralDirection(f->x, f->y, burn->x, burn->y);
	if (f->attackDirection >= 8) {
		f->attackDirection = 0;
	}
	f->waitTicks--;
	if (f->waitTicks <= 0) {
		f->waitTicksMissile = 20;
		if (!prefectGoFightFire(walkerId, f)) {
			struct Data_Building *b = &Data_Buildings[f->buildingId];
			int xRoad, yRoad;
			if (Terrain_getClosestRoadWithinRadius(b->x, b->y, b->size, 2, &xRoad, &yRoad)) {
				f->actionState = FigureActionState_73_PrefectReturning;
				f->destinationX = xRoad;
				f->destinationY = yRoad;
				FigureRoute_remove(walkerId);
			} else {
				f->state = FigureState_Dead;
			}
		}
	}
}

static int prefectTargetIsAlive(struct Data_Walker *f)
{
	if (f->targetFigureId <= 0) {
		return 0;
	}
	struct Data_Walker *fTarget = &Data_Walkers[f->targetFigureId];
	if (!FigureIsDead(f->targetFigureId) && fTarget->createdSequence == f->targetFigureCreatedSequence) {
		return 1;
	}
	return 0;
}

void FigureAction_prefect(int walkerId)
{
	struct Data_Walker *f = &Data_Walkers[walkerId];
	struct Data_Building *b = &Data_Buildings[f->buildingId];
	
	f->terrainUsage = FigureTerrainUsage_Roads;
	f->useCrossCountry = 0;
	f->maxRoamLength = 640;
	if (!BuildingIsInUse(f->buildingId) || b->figureId != walkerId) {
		f->state = FigureState_Dead;
	}
	FigureActionIncreaseGraphicOffset(f, 12);
	
	// special actions
	if (!prefectGoFightEnemy(walkerId, f)) {
		prefectGoFightFire(walkerId, f);
	}
	switch (f->actionState) {
		case FigureActionState_150_Attack:
			FigureAction_Common_handleAttack(walkerId);
			break;
		case FigureActionState_149_Corpse:
			FigureAction_Common_handleCorpse(walkerId);
			break;
		case FigureActionState_70_PrefectCreated:
			f->isGhost = 1;
			f->graphicOffset = 0;
			f->waitTicks--;
			if (f->waitTicks <= 0) {
				int xRoad, yRoad;
				if (Terrain_getClosestRoadWithinRadius(b->x, b->y, b->size, 2, &xRoad, &yRoad)) {
					f->actionState = FigureActionState_71_PrefectEnteringExiting;
					FigureAction_Common_setCrossCountryDestination(walkerId, f, xRoad, yRoad);
					f->roamLength = 0;
				} else {
					f->state = FigureState_Dead;
				}
			}
			break;
		case FigureActionState_71_PrefectEnteringExiting:
			f->useCrossCountry = 1;
			f->isGhost = 1;
			if (FigureMovement_crossCountryWalkTicks(walkerId, 1) == 1) {
				if (Data_Grid_buildingIds[f->gridOffset] == f->buildingId) {
					// returned to own building
					f->state = FigureState_Dead;
				} else {
					f->actionState = FigureActionState_72_PrefectRoaming;
					FigureMovement_initRoaming(walkerId);
					f->roamLength = 0;
				}
			}
			break;
		case FigureActionState_72_PrefectRoaming:
			f->isGhost = 0;
			f->roamLength++;
			if (f->roamLength >= f->maxRoamLength) {
				int xRoad, yRoad;
				if (Terrain_getClosestRoadWithinRadius(b->x, b->y, b->size, 2, &xRoad, &yRoad)) {
					f->actionState = FigureActionState_73_PrefectReturning;
					f->destinationX = xRoad;
					f->destinationY = yRoad;
					FigureRoute_remove(walkerId);
				} else {
					f->state = FigureState_Dead;
				}
			}
			FigureMovement_roamTicks(walkerId, 1);
			break;
		case FigureActionState_73_PrefectReturning:
			FigureMovement_walkTicks(walkerId, 1);
			if (f->direction == DirFigure_8_AtDestination) {
				f->actionState = FigureActionState_71_PrefectEnteringExiting;
				FigureAction_Common_setCrossCountryDestination(walkerId, f, b->x, b->y);
				f->roamLength = 0;
			} else if (f->direction == DirFigure_9_Reroute || f->direction == DirFigure_10_Lost) {
				f->state = FigureState_Dead;
			}
			break;
		case FigureActionState_74_PrefectGoingToFire:
			f->terrainUsage = FigureTerrainUsage_Any;
			FigureMovement_walkTicks(walkerId, 1);
			if (f->direction == DirFigure_8_AtDestination) {
				f->actionState = FigureActionState_75_PrefectAtFire;
				FigureRoute_remove(walkerId);
				f->roamLength = 0;
				f->waitTicks = 50;
			} else if (f->direction == DirFigure_9_Reroute || f->direction == DirFigure_10_Lost) {
				f->state = FigureState_Dead;
			}
			break;
		case FigureActionState_75_PrefectAtFire:
			prefectExtinguishFire(walkerId, f);
			break;
		case FigureActionState_76_PrefectGoingToEnemy:
			f->terrainUsage = FigureTerrainUsage_Any;
			if (!prefectTargetIsAlive(f)) {
				int xRoad, yRoad;
				if (Terrain_getClosestRoadWithinRadius(b->x, b->y, b->size, 2, &xRoad, &yRoad)) {
					f->actionState = FigureActionState_73_PrefectReturning;
					f->destinationX = xRoad;
					f->destinationY = yRoad;
					FigureRoute_remove(walkerId);
					f->roamLength = 0;
				} else {
					f->state = FigureState_Dead;
				}
			}
			FigureMovement_walkTicks(walkerId, 1);
			if (f->direction == DirFigure_8_AtDestination) {
				f->destinationX = Data_Walkers[f->targetFigureId].x;
				f->destinationY = Data_Walkers[f->targetFigureId].y;
				FigureRoute_remove(walkerId);
			} else if (f->direction == DirFigure_9_Reroute || f->direction == DirFigure_10_Lost) {
				f->state = FigureState_Dead;
			}
			break;
	}
	// graphic id
	int dir;
	if (f->actionState == FigureActionState_75_PrefectAtFire ||
		f->actionState == FigureActionState_150_Attack) {
		dir = f->attackDirection;
	} else if (f->direction < 8) {
		dir = f->direction;
	} else {
		dir = f->previousTileDirection;
	}
	WalkerActionNormalizeDirection(dir);
	switch (f->actionState) {
		case FigureActionState_74_PrefectGoingToFire:
			f->graphicId = GraphicId(ID_Graphic_Figure_PrefectWithBucket) +
				dir + 8 * f->graphicOffset;
			break;
		case FigureActionState_75_PrefectAtFire:
			f->graphicId = GraphicId(ID_Graphic_Figure_PrefectWithBucket) +
				dir + 96 + 8 * (f->graphicOffset / 2);
			break;
		case FigureActionState_150_Attack:
			if (f->attackGraphicOffset >= 12) {
				f->graphicId = GraphicId(ID_Graphic_Figure_Prefect) +
					104 + dir + 8 * ((f->attackGraphicOffset - 12) / 2);
			} else {
				f->graphicId = GraphicId(ID_Graphic_Figure_Prefect) + 104 + dir;
			}
			break;
		case FigureActionState_149_Corpse:
			f->graphicId = GraphicId(ID_Graphic_Figure_Prefect) +
				96 + WalkerActionCorpseGraphicOffset(f);
			break;
		default:
			f->graphicId = GraphicId(ID_Graphic_Figure_Prefect) +
				dir + 8 * f->graphicOffset;
			break;
	}
}

void FigureAction_worker(int walkerId)
{
	struct Data_Walker *f = &Data_Walkers[walkerId];
	f->terrainUsage = FigureTerrainUsage_Roads;
	f->useCrossCountry = 0;
	f->maxRoamLength = 384;
	if (!BuildingIsInUse(f->buildingId) ||
		Data_Buildings[f->buildingId].figureId != walkerId) {
		f->state = FigureState_Dead;
	}
}
