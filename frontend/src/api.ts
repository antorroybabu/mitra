export type Post={id:number;author_id:number;body:string;created_at:string};
export type Page<T>={items:T[];next_cursor?:string|null};
export async function api<T>(path:string,init:RequestInit={}):Promise<T>{const r=await fetch(path,{...init,headers:{'Content-Type':'application/json',...(init.headers||{})},credentials:'include'});if(!r.ok)throw new Error(`API ${r.status}`);return r.json() as Promise<T>}
export const getFeed=()=>api<Page<Post>>('/v1/feed');
export const createPost=(body:string)=>api<Post>('/v1/posts',{method:'POST',body:JSON.stringify({body})});
