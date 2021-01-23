/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static const unsigned int smartgaps = 0;       /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char col0[]            = "#1b2229";
static const char col1[]            = "#ff6c6b";
static const char col2[]            = "#98be65";
static const char col3[]            = "#ecbe7b";
static const char col4[]            = "#2257a0";
static const char col5[]            = "#a9a1e1";
static const char col6[]            = "#5699af";
static const char col7[]            = "#5b6268";
static const char col8[]            = "#1c1f24";
static const char col9[]            = "#da8548";
static const char col10[]           = "#4db5bd";
static const char col11[]           = "#ecbe7b";
static const char col12[]           = "#51afef";
static const char col13[]           = "#c678dd";
static const char col14[]           = "#46d9ff";
static const char col15[]           = "#bbc2cf";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm]  = { col15, col0, col0  },
	[SchemeSel]   = { col5,  col0, col13 },
	[SchemeCol0]  = { col0,	 col0, col0  },
	[SchemeCol1]  = { col1,  col0, col0  },
	[SchemeCol2]  = { col2,  col0, col0  },
	[SchemeCol3]  = { col3,  col0, col0  },
	[SchemeCol4]  = { col4,  col0, col0  },
	[SchemeCol5]  = { col5,  col0, col0  },
	[SchemeCol6]  = { col6,  col0, col0  },
	[SchemeCol7]  = { col7,  col0, col0  },
	[SchemeCol8]  = { col8,  col0, col0  },
	[SchemeCol9]  = { col9,  col0, col0  },
	[SchemeCol10] = { col10, col0, col0  },
	[SchemeCol11] = { col11, col0, col0  },
	[SchemeCol12] = { col12, col0, col0  },
	[SchemeCol13] = { col13, col0, col0  },
	[SchemeCol14] = { col14, col0, col0  },
	[SchemeCol15] = { col15, col0, col0  },
};
static const char dmenufont[] = "monospace:size=12";
static const char *fonts[]          = {
	"monospace:size=12",
	"Apple Color Emoji:size=10",
};

/* tagging */
static const char *tags[] = { "ﲵ", "", "卑", "ﱢ", "ﯾ", "", "", "阮", "ﭮ" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "﩯",      tile },    /* Default: master on left, slaves on right */
	{ "ﱢ",      monocle }, /* All windows on top of each other */
	{ "זּ",      NULL },    /* No layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col0, "-nf", col15, "-sb", col4, "-sf", col15, NULL };
static const char *termcmd[]  = { "alacritty", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },

	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_y,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_o,      incnmaster,     {.i = +1} },
	{ MODKEY|ShiftMask,             XK_o,      incnmaster,     {.i = -1} },
	{ MODKEY,                       XK_Tab,    view,           {0} },

	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },

	{ MODKEY,                       XK_space,  zoom,           {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY|ControlMask,           XK_space,  togglefullscr,  {0} },

	{ MODKEY,                       XK_Left,  focusmon,       {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Left,  tagmon,         {.i = -1 } },
	{ MODKEY,                       XK_Right, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Right, tagmon,         {.i = +1 } },

	{ MODKEY,                       XK_b,      spawn,          SHCMD("$BROWSER") },
	{ MODKEY|ShiftMask,             XK_b,      spawn,          SHCMD("$BROWSER -incognito") },
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_e,      spawn,          SHCMD("$VISUAL") },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },

	/* { MODKEY,                       XK_F1,     spawn,          SHCMD("") }, */
	/* { MODKEY,                       XK_F2,     spawn,          SHCMD("") }, */
	/* { MODKEY,                       XK_F3,     spawn,          SHCMD("") }, */
	/* { MODKEY,                       XK_F4,     spawn,          SHCMD("") }, */
	/* { MODKEY,                       XK_F5,     spawn,          SHCMD("") }, */
	/* { MODKEY,                       XK_F6,     spawn,          SHCMD("") }, */
	/* { MODKEY,                       XK_F7,     spawn,          SHCMD("") }, */
	/* { MODKEY,                       XK_F8,     spawn,          SHCMD("") }, */
	/* { MODKEY,                       XK_F9,     spawn,          SHCMD("") }, */
	/* { MODKEY,                       XK_F10,    spawn,          SHCMD("") }, */
	/* { MODKEY,                       XK_F11,    spawn,          SHCMD("") }, */
	/* { MODKEY,                       XK_F12,    spawn,          SHCMD("") }, */

	{ 0,                            XK_Print,  spawn,          SHCMD("screenshot -m f") },
	{ ShiftMask,                    XK_Print,  spawn,          SHCMD("screenshot -m d") },

	{ 0, XF86XK_AudioMute,                     spawn,          SHCMD("pamixer -t; sigdsblocks 1") },
	{ 0, XF86XK_AudioRaiseVolume,              spawn,          SHCMD("pamixer -i 1; sigdsblocks 1") },
	{ 0, XF86XK_AudioLowerVolume,              spawn,          SHCMD("pamixer -d 1; sigdsblocks 1") },
	/* { 0, XF86XK_AudioPlay,                     spawn,          SHCMD("") }, */
	/* { 0, XF86XK_AudioStop,                     spawn,          SHCMD("") }, */
	/* { 0, XF86XK_AudioPrev,                     spawn,          SHCMD("") }, */
	/* { 0, XF86XK_AudioNext,                     spawn,          SHCMD("") }, */
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigdsblocks,    {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdsblocks,    {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdsblocks,    {.i = 3} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

