import React from 'react';
import { createRoot } from 'react-dom/client';
import './style.css';

function App(){return <div className="app"><header><strong>MITRA</strong><nav>Home · Explore · Notifications · Profile</nav></header><main><aside><button>Home</button><button>Explore</button><button>Messages</button><button>Bookmarks</button></aside><section><div className="composer"><textarea placeholder="What's happening?"/><button>Post</button></div><article><b>Antor Roy</b><p>Welcome to MITRA — a privacy-first social platform.</p><small>0 likes · 0 comments · 0 reposts</small></article></section><aside className="right"><h3>Trending</h3><p>#Technology</p><p>#Programming</p><p>#MITRA</p></aside></main></div>}
createRoot(document.getElementById('root')!).render(<React.StrictMode><App/></React.StrictMode>);
