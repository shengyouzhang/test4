package com.zsy.frame.sample.jni.control.base;

import java.text.Collator;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import android.app.ListActivity;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.content.pm.ResolveInfo;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.ListView;
import android.widget.SimpleAdapter;

import com.zsy.frame.sample.jni.config.Constants;

public class JNIMainAct extends ListActivity {

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		Intent intent = getIntent();
		String path = intent.getStringExtra(Constants.MAIN_LIST_VIEW_ITEMNAME);// 提取Intent信息中的Path信息

		if (path == null) {
			path = "";
		}

		setListAdapter(new SimpleAdapter(this, getData(path), android.R.layout.simple_list_item_1, new String[] { "title" }, new int[] { android.R.id.text1 }));
		getListView().setTextFilterEnabled(true);// 根据path信息设置当前的列表
	}

	@Override
	protected void onDestroy() {
		super.onDestroy();
		Log.i(Constants.LOGCAT_TAG_NAME, "Main Activity Destory");
		// Process.killProcess(Process.myPid());
		System.exit(0);
	}

	/**
	 * @description：获取的菜单列表数据
	 * @author samy
	 * @date 2015-1-26 上午10:54:56
	 * @param prefix是当前所处的目录
	 */
	protected List<Map<String, Object>> getData(String prefix) {
		List<Map<String, Object>> myData = new ArrayList<Map<String, Object>>();

		// 除了入口Activity的API Demos之外，其他的Activity都属于Intent.CATEGORY_SAMPLE_CODE
		// CATEGORY_SAMPLE_CODE;作为一个简单的代码示例使用（一般情况下不使用）;
		// 该CATEGORY 用于通过queryIntent Activities获得Activity列表，通过ResolveInfo解析列表中某个Activity的信息
		// <action android:name="android.intent.action.MAIN" />
		// <category android:name="android.intent.category.SAMPLE_CODE" />
		// Intent mainIntent = new Intent(Intent.ACTION_MAIN, null);
		Intent mainIntent = new Intent();
		mainIntent.setAction(Intent.ACTION_MAIN);
		mainIntent.addCategory(Intent.CATEGORY_SAMPLE_CODE);
		PackageManager pm = getPackageManager();
		List<ResolveInfo> list = pm.queryIntentActivities(mainIntent, 0);

		if (null == list) { return myData; }

		String[] prefixPath;
		String prefixWithSlash = prefix;

		if (prefix.equals("")) {
			prefixPath = null;
		}
		else {
			prefixPath = prefix.split("/");
			prefixWithSlash = prefix + "/";
		}

		Map<String, Boolean> entries = new HashMap<String, Boolean>();
		int len = list.size();

		for (int i = 0; i < len; i++) {
			ResolveInfo info = list.get(i);
			CharSequence labelSeq = info.loadLabel(pm);
			String label = labelSeq != null ? labelSeq.toString() : info.activityInfo.name;

			if (prefixWithSlash.length() == 0 || label.startsWith(prefixWithSlash)) {
				String[] labelPath = label.split("/");
				String nextLabel = prefixPath == null ? labelPath[0] : labelPath[prefixPath.length];

				if ((prefixPath != null ? prefixPath.length : 0) == labelPath.length - 1) {
					// 首页显示
					addItem(myData, nextLabel, activityIntent(info.activityInfo.applicationInfo.packageName, info.activityInfo.name));
				}
				else {
					if (entries.get(nextLabel) == null) {
						// 非首页显示
						addItem(myData, nextLabel, browseIntent(prefix.equals("") ? nextLabel : prefix + "/" + nextLabel));
						entries.put(nextLabel, true);
					}
				}
			}
		}

		Collections.sort(myData, sDisplayNameComparator);

		return myData;
	}

	private final static Comparator<Map<String, Object>> sDisplayNameComparator = new Comparator<Map<String, Object>>() {
		private final Collator collator = Collator.getInstance();

		public int compare(Map<String, Object> map1, Map<String, Object> map2) {
			return collator.compare(map1.get("title"), map2.get("title"));
		}
	};

	protected Intent activityIntent(String pkg, String componentName) {
		Intent result = new Intent();
		result.setClassName(pkg, componentName);
		return result;
	}

	protected Intent browseIntent(String path) {
		Intent result = new Intent();
		result.setClass(this, JNIMainAct.class);
		result.putExtra(Constants.MAIN_LIST_VIEW_ITEMNAME, path);
		return result;
	}

	protected void addItem(List<Map<String, Object>> data, String name, Intent intent) {
		Map<String, Object> temp = new HashMap<String, Object>();
		temp.put("title", name);
		temp.put("intent", intent);
		data.add(temp);
	}

	@Override
	@SuppressWarnings("unchecked")
	protected void onListItemClick(ListView l, View v, int position, long id) {
		Map<String, Object> map = (Map<String, Object>) l.getItemAtPosition(position);

		Intent intent = (Intent) map.get("intent");
		startActivity(intent);
	}
}
