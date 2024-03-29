#include "cbase.h"
#include "multiplayer_animstate.h"
#include "basenetworkedragdoll_cl.h"
#include "c_basetempentity.h"

#define CBaseNetworkedPlayer C_BaseNetworkedPlayer

class C_BaseNetworkedPlayer : public C_BasePlayer {
public:
	DECLARE_CLASS(C_BaseNetworkedPlayer,C_BasePlayer);
	DECLARE_CLIENTCLASS();
	DECLARE_PREDICTABLE();
	C_BaseNetworkedPlayer();

	virtual void Respawn(); // Spawn() is called once, this is called every time

	// Implement multiplayer ragdolls
	C_BaseAnimating* BecomeRagdollOnClient() { return NULL; }
	virtual IRagdoll* GetRepresentativeRagdoll() const;

	// Implement CMultiplayerAnimState
	virtual void DoAnimationEvent( PlayerAnimEvent_t event, int nData = 0 );
	virtual void UpdateClientSideAnimation();
	virtual void PostDataUpdate( DataUpdateType_t updateType );
	virtual const QAngle& EyeAngles();
	virtual const QAngle& GetRenderAngles();
protected:
	CMultiPlayerAnimState* m_PlayerAnimState;

	QAngle	m_angEyeAngles;
	bool	m_bSpawnInterpCounter;
	bool	m_bSpawnInterpCounterCache;
	CInterpolatedVar<QAngle>	m_iv_angEyeAngles;
	EHANDLE	m_hRagdoll;
};

// -------------------------------------------------------------------------------- //
// Player animation event. Sent to the client when a player fires, jumps, reloads, etc..
// -------------------------------------------------------------------------------- //

class C_TEPlayerAnimEvent : public C_BaseTempEntity
{
public:
	DECLARE_CLASS( C_TEPlayerAnimEvent, C_BaseTempEntity );
	DECLARE_CLIENTCLASS();

	virtual void PostDataUpdate( DataUpdateType_t updateType );

public:
	CNetworkHandle( CBasePlayer, m_hPlayer );
	CNetworkVar( int, m_iEvent );
	CNetworkVar( int, m_nData );
};