/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 5;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int vertpad            = 0;       /* vertical padding of bar */
static const int sidepad            = 0;       /* horizontal padding of bar */
static const int horizpadbar        = 5;        /* horizontal padding for statusbar */
static const int vertpadbar         = 10;        /* vertical padding for statusbar */
static const char *fonts[]          = { "monospace:size=14","Wuncon Siji:pixelsize=35","SauceCodePro Nerd Font:pixelsize=35" };
static const char dmenufont[]       = "monospace:size=14";
static const char col_gray1[]       = "#333333";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#444444";
static const char col_border[]      = "#000000";
static const char col_border_sel[]  = "#FFB90F";
static const unsigned int baralpha = 0xE0;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_border},
	[SchemeSel]  = { col_border_sel, col_cyan,  col_border_sel  },
	[SchemeHid]  = { col_cyan,  col_gray1, col_cyan  },
};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
	[SchemeHid]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = {"一", "二", "三", "四", "五", "六", "七", "八", "九"};
// static const char *tags[] = { "一", "2", "3", "4", "5", "6", "7", "8", "9" };
// static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

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
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "平铺",      tile },    /* first entry is default */
	{ "全屏",      monocle },
	{ "浮动",      NULL },    /* no layout function means floating behavior */

};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ Mod1Mask,                     KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ Mod1Mask|ShiftMask,           KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#define STATUSBAR "dwmblocks"

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "alacritty", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "200x60", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ Mod1Mask|ShiftMask,           XK_p,      spawn,          {.v = dmenucmd } },
	{ Mod1Mask|ShiftMask,           XK_Return, spawn,          {.v = termcmd } },
   { MODKEY,                       XK_b,      togglebar,      {0} },
	{ Mod1Mask,                     XK_j,      focusstackvis,     {.i = +1 } },
	{ Mod1Mask,                     XK_k,      focusstackvis,     {.i = -1 } },
	{ Mod1Mask,                     XK_i,      incnmaster,     {.i = +1 } },
	{ Mod1Mask,                     XK_d,      incnmaster,     {.i = -1 } },
	{ Mod1Mask|ShiftMask,           XK_h,      setmfact,       {.f = -0.05} },
	{ Mod1Mask|ShiftMask,           XK_l,      setmfact,       {.f = +0.05} },
	//{ Mod1Mask,                     XK_h,      focusstack,     {.i = -1} },
	//{ Mod1Mask,                     XK_l,      focusstack,     {.i = +1} },
	{ Mod1Mask,                     XK_Return, zoom,           {0} },
	{ Mod1Mask,                     XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[2]} },
	{ Mod1Mask|ShiftMask,           XK_f,      fullscreen,     {0} },
	//{ Mod1Mask,                     XK_Tab,    focusstack,     {.i = +1 } },
	//{ Mod1Mask|ShiftMask,           XK_Tab,    focusstack,     {.i = -1 } },
	{ MODKEY,                     XK_Tab,  setlayout,      {0} },
	//{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },

	{ MODKEY|ControlMask,           XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ControlMask|ShiftMask, XK_0,      tag,            {.ui = ~0 } },

	{ MODKEY,                       XK_grave,  focusmon,       {.i = -1 } },
	//{ Mod1Mask,                     XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_grave,  tagmon,         {.i = -1 } },
	//{ Mod1Mask|ShiftMask,           XK_period, tagmon,         {.i = +1 } },

	{ ShiftMask,                    XK_space,  togglescratch,  {.v = scratchpadcmd } },


   { Mod1Mask|ShiftMask,             XK_j,      rotatestack,    {.i = +1 } },
   { Mod1Mask|ShiftMask,             XK_k,      rotatestack,    {.i = -1 } },
//  { MODKEY,                       XK_j,      focusstackvis,  {.i = +1 } },
//  { MODKEY,                       XK_k,      focusstackvis,  {.i = -1 } },
//  { MODKEY|ShiftMask,             XK_j,      focusstackhid,  {.i = +1 } },
//  { MODKEY|ShiftMask,             XK_k,      focusstackhid,  {.i = -1 } },
//
//  { MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
//  { MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
//  { MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
//  { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
//  { MODKEY,                       XK_Return, zoom,           {0} },
//  { MODKEY,                       XK_Tab,    view,           {0} },
//  { MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
//  { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
//  { MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
//  { MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
//  { MODKEY|ShiftMask,             XK_f,      fullscreen,     {0} },
//  { MODKEY,                       XK_space,  setlayout,      {0} },
//  { MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
//  { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
//  { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
//  { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
//  { MODKEY,                       XK_period, focusmon,       {.i = +1 } },
//  { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
//  { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
//  { MODKEY,                       XK_s,      show,           {0} },
//  { MODKEY,                       XK_h,      hide,           {0} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button1,        togglewin,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

